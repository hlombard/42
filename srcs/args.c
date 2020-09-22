/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 13:36:55 by hlombard          #+#    #+#             */
/*   Updated: 2020/09/14 19:28:22 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int		arg_is_valid_hash(char *str, t_hash *hash)
{
	int i;

	i = -1;
	while (g_hash[++i].name != NULL)
	{
		if (!ft_strcmp(str, g_hash[i].name))
		{
			hash->algo_type = i;
			return (1);
		}
	}
	error_command(str);
	return (0);
}

int				args_check(int ac, char **av, t_hash *hash)
{
	if (ac < 2)
	{
		ft_putstr("usage: ft_ssl command [command opts] [command args]\n");
		return (0);
	}
	if (!arg_is_valid_hash(av[1], hash))
		return (0);
	flags_set(ac, av, 1, hash);
	return (1);
}

static int		is_not_to_hash(char **av, t_hash *hash)
{
	hash->arg_index++;
	if (!av[hash->arg_index])
		return (0);
	if (!ft_strcmp("-q", av[hash->arg_index]) ||
			!ft_strcmp("-r", av[hash->arg_index]))
		return (flags_set_q_r(av, hash));
	else if (!ft_strcmp("-s", av[hash->arg_index]))
	{
		hash->flag_s_pos = hash->arg_index;
		return (0);
	}
	else if (!ft_strcmp("-p", av[hash->arg_index]))
		return (flags_p_special(hash));
	else
	{
		return (0);
	}
}

void			args_process(char *str, char **argv, t_hash *hash)
{
	if (hash->arg_index == hash->flag_s_pos)
	{
		hash->arg_index++;
		if (argv[hash->arg_index] == NULL)
			quit_s_option_error(hash);
		args_process_s(argv, hash);
		while (is_not_to_hash(argv, hash))
			;
	}
	else
	{
		str = read_file(argv[hash->arg_index], hash);
		if (str != NULL)
		{
			g_hash[hash->algo_type].hashfunc(str, hash);
			g_hash[hash->algo_type].printfunc(argv[hash->arg_index], hash);
			free(str);
		}
		hash->arg_index++;
	}
}

void			args_process_s(char **argv, t_hash *hash)
{
	hash->print_quotes = 1;
	hash->read = ft_strlen(argv[hash->arg_index]);
	g_hash[hash->algo_type].hashfunc(argv[hash->arg_index], hash);
	g_hash[hash->algo_type].printfunc(argv[hash->arg_index], hash);
	hash->print_quotes = 0;
}
