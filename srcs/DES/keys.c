/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:37:36 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/31 01:42:50 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static uint8_t g_pc1[56] = {57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26,
	18, 10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39,
	31, 23, 15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13,
	5, 28, 20, 12, 4};

static uint8_t g_pc2[48] = {14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21,
	10, 23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55,
	30, 40, 51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};

unsigned char g_p[32] = {
	16, 7, 20, 21, 29, 12, 28, 17,
	1, 15, 23, 26, 5, 18, 31, 10,
	2, 8, 24, 14, 32, 27, 3, 9,
	19, 13, 30, 6, 22, 11, 4, 25};

static uint8_t g_leftshift_nb[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1,
	2, 2, 2, 2, 2, 2, 1};

static char			*concatenate_pass_salt(char *pass, uint64_t salt,
					size_t *size)
{
	char	*ret;
	char	*salt_str;
	int		i;
	uint8_t	*p;

	if (!(salt_str = ft_memalloc(sizeof(uint64_t) + 1)))
		exit(EXIT_FAILURE);
	salt = reverse_endian64(salt);
	p = (uint8_t*)&salt;
	i = -1;
	while (++i < 8)
		salt_str[i] = (char)p[i];
	*size = ft_strlen(pass) + 8;
	if (!(ret = ft_memjoin_free(pass, salt_str, ft_strlen(pass), 8)))
		exit(EXIT_FAILURE);
	return (ret);
}

static uint64_t		key_generate(char *pass, uint64_t salt, int key_type)
{
	t_hash		hash;
	char		*msg;
	uint64_t	key;

	ft_bzero(&hash, sizeof(t_hash));
	msg = concatenate_pass_salt(pass, salt, &hash.read);
	g_hash[MD5].hashfunc(msg, &hash);
	if (key_type == 1)
		key = uint32_join(reverse_endian32(hash.h_32[0]),
			reverse_endian32(hash.h_32[1]));
	else
		key = uint32_join(reverse_endian32(hash.h_32[2]),
			reverse_endian32(hash.h_32[3]));
	free(msg);
	return (key);
}

void				key_get_format(t_des *des)
{
	des->salt_format = get_salt(des);
	if (!des->key)
		des->key_format = key_generate(des->pass, des->salt_format, 1);
	else
		des->key_format = hex_str_to_64(des->key);
	if (des->des_type == CBC || des->des_type == DES_DEF
		|| des->des_type == CFB)
	{
		des->iv_format = des->iv ? hex_str_to_64(des->iv)
		: key_generate(des->pass, des->salt_format, 2);
	}
	free(des->salt_str);
	free(des->pass);
}

void				create_subkeys(t_des *des, int encrypt)
{
	uint64_t	parity_key;
	uint32_t	half1;
	uint32_t	half2;
	int			i;
	int			rotate_nb;

	parity_key = permute_bits_from_table(des->key_format, g_pc1, 64, 56);
	half1 = (uint32_t)((parity_key >> 28) & 0xfffffff);
	half2 = (uint32_t)(parity_key & 0xfffffff);
	i = -1;
	while (++i < 16)
	{
		rotate_nb = g_leftshift_nb[i];
		while (rotate_nb--)
		{
			half1 = (0x0fffffff & (half1 << 1)) | (0x00000001 & (half1 >> 27));
			half2 = (0x0fffffff & (half2 << 1)) | (0x00000001 & (half2 >> 27));
		}
		if (encrypt != 1)
			des->subkeys[15 - i] = permute_bits_from_table(half2
			+ ((uint64_t)half1 << 28), g_pc2, 56, 48);
		else
			des->subkeys[i] = permute_bits_from_table(half2
			+ ((uint64_t)half1 << 28), g_pc2, 56, 48);
	}
}
