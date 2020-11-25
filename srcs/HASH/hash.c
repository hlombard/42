/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 23:01:10 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/14 23:01:30 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void			hash_process_s(char **argv, t_hash *hash)
{
	hash->print_quotes = 1;
	hash->read = ft_strlen(argv[hash->arg_index]);
	g_hash[hash->hash_type].hashfunc(argv[hash->arg_index], hash);
	g_hash[hash->hash_type].printfunc(argv[hash->arg_index], hash);
	hash->print_quotes = 0;
}

static int			is_not_to_hash(char **av, t_hash *hash)
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

static void			hash_args_process(char *str, char **argv, t_hash *hash)
{
	if (hash->arg_index == hash->flag_s_pos)
	{
		hash->arg_index++;
		if (argv[hash->arg_index] == NULL)
			quit_s_option_error(hash);
		hash_process_s(argv, hash);
		while (is_not_to_hash(argv, hash))
			;
	}
	else
	{
		str = hash_read_file(argv[hash->arg_index], hash);
		if (str != NULL)
		{
			g_hash[hash->hash_type].hashfunc(str, hash);
			g_hash[hash->hash_type].printfunc(argv[hash->arg_index], hash);
			free(str);
		}
		hash->arg_index++;
	}
}

void				hash_load(char *str, t_hash *hash)
{
	int i;

	i = -1;
	while (g_hash[++i].name != NULL)
	{
		if (!ft_strcmp(str, g_hash[i].name))
			hash->hash_type = i;
	}
}

void				hash_loop(int argc, char **argv, t_hash *hash)
{
	char *str;

	str = NULL;
	if (hash->flags & FLAG_HASH_P || !hash->no_file)
		hash_read_input(str, hash);
	while (hash->arg_index < argc)
		hash_args_process(str, argv, hash);
}
