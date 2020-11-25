/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 23:04:10 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/14 23:04:22 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		set_hash_values_for_chunk(uint32_t *i, t_hash *hash)
{
	hash->var_32[0] = hash->h_32[0];
	hash->var_32[1] = hash->h_32[1];
	hash->var_32[2] = hash->h_32[2];
	hash->var_32[3] = hash->h_32[3];
	hash->var_32[4] = 0;
	hash->var_32[5] = 0;
	*i = 0;
}

static void	md5_bitsmess(int i, t_hash *hash)
{
	if (i < 16)
	{
		hash->var_32[4] = (hash->var_32[1] & hash->var_32[2]) |
			((~hash->var_32[1]) & hash->var_32[3]);
		hash->var_32[5] = i;
	}
	else if (i < 32)
	{
		hash->var_32[4] = (hash->var_32[3] & hash->var_32[1]) |
			((~hash->var_32[3]) & hash->var_32[2]);
		hash->var_32[5] = (5 * i + 1) % 16;
	}
	else if (i < 48)
	{
		hash->var_32[4] = hash->var_32[1] ^ hash->var_32[2] ^ hash->var_32[3];
		hash->var_32[5] = (3 * i + 5) % 16;
	}
	else
	{
		hash->var_32[4] = hash->var_32[2] ^ (hash->var_32[1] |
			(~hash->var_32[3]));
		hash->var_32[5] = (7 * i) % 16;
	}
}

static void	md5_adjust(uint32_t k, uint32_t w, uint32_t r, t_hash *hash)
{
	uint32_t tmp;

	tmp = hash->var_32[3];
	hash->var_32[3] = hash->var_32[2];
	hash->var_32[2] = hash->var_32[1];
	hash->var_32[1] = hash->var_32[1] + l_rotate32(hash->var_32[0]
	+ hash->var_32[4] + k + w, r);
	hash->var_32[0] = tmp;
}

static void	md5_add_chunk(t_hash *hash)
{
	hash->h_32[0] += hash->var_32[0];
	hash->h_32[1] += hash->var_32[1];
	hash->h_32[2] += hash->var_32[2];
	hash->h_32[3] += hash->var_32[3];
	hash->offset += 64;
}

void		md5_hash(char *str, t_hash *hash)
{
	uint32_t	*k;
	uint32_t	*r;
	uint32_t	i;
	uint8_t		*msg;

	k = md5_init_sines();
	r = md5_init_shift_amount();
	md5_init_hash(hash);
	msg = md5_init_padding(str, hash->read, hash);
	while (hash->offset < hash->msg_len)
	{
		hash->w32 = (uint32_t *)(msg + hash->offset);
		set_hash_values_for_chunk(&i, hash);
		while (i < 64)
		{
			md5_bitsmess(i, hash);
			md5_adjust(k[i], hash->w32[hash->var_32[5]], r[i], hash);
			i++;
		}
		md5_add_chunk(hash);
	}
	free(msg);
}
