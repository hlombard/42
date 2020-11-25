/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 01:44:02 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/31 00:39:57 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		command_start_hash(int argc, char **argv, t_hash *hash)
{
	hash_load(argv[1], hash);
	hash_flags_set(argc, argv, 1, hash);
	hash_loop(argc, argv, hash);
}

void		command_start_des(int argc, char **argv, t_des *des)
{
	des_load(argv[1], des);
	des_flags_set(argc, argv, des);
	des_manage(des);
}

void		command_start_encoding(int argc, char **argv, t_encoding *encoding)
{
	enc_load(argv[1], encoding);
	enc_flags_set(argc, argv, encoding);
	enc_manage(encoding);
}

static int	command_is_valid(char *str)
{
	int i;

	i = -1;
	while (g_hash[++i].name != NULL)
	{
		if (!ft_strcmp(str, g_hash[i].name))
			return (HASH);
	}
	i = -1;
	while (g_des[++i].name != NULL)
	{
		if (!ft_strcmp(str, g_des[i].name))
			return (DES);
	}
	i = -1;
	while (g_enc[++i].name != NULL)
	{
		if (!ft_strcmp(str, g_enc[i].name))
			return (ENCODING);
	}
	error_command(str);
	return (0);
}

int			command_check(int ac, char **av)
{
	if (ac < 2)
	{
		ft_putstr("usage: ft_ssl command [command opts] [command args]\n");
		return (0);
	}
	return (command_is_valid(av[1]));
}
