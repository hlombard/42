/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 23:05:40 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/14 23:05:41 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	*sha256_init_padding(char *str, size_t len, t_hash *hash)
{
	size_t		i;
	uint32_t	*msg;

	hash->msg_len = len * 8 + 1;
	while (hash->msg_len % 512 != 448)
		hash->msg_len++;
	hash->msg_len = (hash->msg_len + 64) / 512;
	if (!(msg = ft_calloc(hash->msg_len, 64)))
		failed_allocate_exit("Failed to calloc msg\n");
	ft_memcpy((char*)msg, str, len);
	((char*)msg)[len] = 0x80;
	i = 0;
	while (i < (hash->msg_len * 16))
	{
		msg[i] = reverse_endian32(msg[i]);
		i++;
	}
	msg[((hash->msg_len * 512 - 64) / 32) + 1] = len * 8;
	hash->offset = 0;
	return (msg);
}

void		sha256_init_hash(t_hash *hash)
{
	if (!ft_strcmp(g_hash[hash->hash_type].name, "sha256"))
	{
		hash->h_32[0] = SHA256_H0;
		hash->h_32[1] = SHA256_H1;
		hash->h_32[2] = SHA256_H2;
		hash->h_32[3] = SHA256_H3;
		hash->h_32[4] = SHA256_H4;
		hash->h_32[5] = SHA256_H5;
		hash->h_32[6] = SHA256_H6;
		hash->h_32[7] = SHA256_H7;
	}
	else
	{
		hash->h_32[0] = SHA224_H0;
		hash->h_32[1] = SHA224_H1;
		hash->h_32[2] = SHA224_H2;
		hash->h_32[3] = SHA224_H3;
		hash->h_32[4] = SHA224_H4;
		hash->h_32[5] = SHA224_H5;
		hash->h_32[6] = SHA224_H6;
		hash->h_32[7] = SHA224_H7;
	}
}

uint32_t	*sha256_init_sines(void)
{
	static uint32_t k[64] = {
		0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
		0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
		0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
		0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa,
		0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
		0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138,
		0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
		0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624,
		0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
		0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f,
		0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

	return (k);
}
