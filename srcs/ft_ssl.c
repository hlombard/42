/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 01:54:22 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/31 00:40:37 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_hash_dispatch		g_hash[] =
{
	{"md5", "MD5", md5_hash, print_md5},
	{"sha224", "SHA224", sha256_hash, print_sha256},
	{"sha256", "SHA256", sha256_hash, print_sha256},
	{"sha384", "SHA384", sha512_hash, print_sha512},
	{"sha512", "SHA512", sha512_hash, print_sha512},
	{NULL, NULL, NULL, NULL},
};

t_des_dispatch		g_des[] =
{
	{"des", "DES", des_encrypt, des_decrypt},
	{"des-ecb", "DES", des_encrypt, des_decrypt},
	{"des-cbc", "DES-CBC", des_encrypt, des_decrypt},
	{"des-cfb", "DES-CFB", des_encrypt, des_decrypt},
	{NULL, NULL, NULL, NULL},
};

t_encoding_dispatch	g_enc[] =
{
	{"base64", "BASE64", base64_encode, base64_decode},
	{NULL, NULL, NULL, NULL},
};

static void			init_structs(t_hash *hash, t_des *des, t_encoding *encoding)
{
	ft_bzero(hash, sizeof(t_hash));
	ft_bzero(des, sizeof(t_des));
	ft_bzero(encoding, sizeof(t_encoding));
}

int					main(int argc, char **argv)
{
	t_hash			hash;
	t_des			des;
	t_encoding		encoding;
	int				ret;

	init_structs(&hash, &des, &encoding);
	if ((ret = command_check(argc, argv)) == 0)
		return (0);
	if (ret == HASH)
		command_start_hash(argc, argv, &hash);
	else if (ret == DES)
		command_start_des(argc, argv, &des);
	else
		command_start_encoding(argc, argv, &encoding);
	return (1);
}
