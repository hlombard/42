/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 13:37:50 by hlombard          #+#    #+#             */
/*   Updated: 2020/09/12 13:38:19 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_dispatch	g_hash[] =
{
	{"md5", "MD5", md5_hash, print_md5},
	{"sha224", "SHA224", sha256_hash, print_sha256},
	{"sha256", "SHA256", sha256_hash, print_sha256},
	{"sha384", "SHA384", sha512_hash, print_sha512},
	{"sha512", "SHA512", sha512_hash, print_sha512},
	{NULL, NULL, NULL, NULL},
};

const char	*get_name(int type, t_hash *hash)
{
	if (type)
		return (g_hash[hash->algo_type].bigname);
	return (g_hash[hash->algo_type].name);
}

void		hash_loop(int argc, char **argv, t_hash *hash)
{
	char *str;

	str = NULL;
	if (hash->flags & FLAG_P || !hash->no_file)
		read_input(str, hash);
	while (hash->arg_index < argc)
	{
		args_process(str, argv, hash);
	}
}

int			main(int argc, char **argv)
{
	t_hash hash;

	ft_bzero(&hash, sizeof(t_hash));
	if (!args_check(argc, argv, &hash))
		return (0);
	hash_loop(argc, argv, &hash);
	return (1);
}
