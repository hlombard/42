/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 23:03:05 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/14 23:03:06 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	sha256_add_chunk(t_hash *hash)
{
	hash->h_32[0] += hash->var_32[0];
	hash->h_32[1] += hash->var_32[1];
	hash->h_32[2] += hash->var_32[2];
	hash->h_32[3] += hash->var_32[3];
	hash->h_32[4] += hash->var_32[4];
	hash->h_32[5] += hash->var_32[5];
	hash->h_32[6] += hash->var_32[6];
	hash->h_32[7] += hash->var_32[7];
}

static void	set_hash_values_for_chunk(t_hash *hash)
{
	int round;

	round = 16;
	while (round < 64)
	{
		hash->tmp32[0] = r_rotate32(hash->w32[round - 15], 7) ^
			r_rotate32(hash->w32[round - 15], 18) ^
				(hash->w32[round - 15] >> 3);
		hash->tmp32[1] = r_rotate32(hash->w32[round - 2], 17) ^
			r_rotate32(hash->w32[round - 2], 19) ^ (hash->w32[round - 2] >> 10);
		hash->w32[round] = hash->w32[round - 16] + hash->tmp32[0]
			+ hash->w32[round - 7] + hash->tmp32[1];
		round++;
	}
	hash->var_32[0] = hash->h_32[0];
	hash->var_32[1] = hash->h_32[1];
	hash->var_32[2] = hash->h_32[2];
	hash->var_32[3] = hash->h_32[3];
	hash->var_32[4] = hash->h_32[4];
	hash->var_32[5] = hash->h_32[5];
	hash->var_32[6] = hash->h_32[6];
	hash->var_32[7] = hash->h_32[7];
}

static void	sha256_bitsmess(int j, uint32_t *k, t_hash *hash)
{
	hash->tmp32[1] = r_rotate32(hash->var_32[4], 6) ^
	r_rotate32(hash->var_32[4], 11) ^ r_rotate32(hash->var_32[4], 25);
	hash->tmp32[2] = (hash->var_32[4] & hash->var_32[5]) ^
	((~hash->var_32[4]) & hash->var_32[6]);
	hash->t1 = hash->var_32[7] + hash->tmp32[1] + hash->tmp32[2] +
	k[j] + hash->w32[j];
	hash->tmp32[0] = r_rotate32(hash->var_32[0], 2) ^
	r_rotate32(hash->var_32[0], 13) ^ r_rotate32(hash->var_32[0], 22);
	hash->tmp32[3] = (hash->var_32[0] & hash->var_32[1]) ^
	(hash->var_32[0] & hash->var_32[2]) ^ (hash->var_32[1] & hash->var_32[2]);
	hash->t2 = hash->tmp32[0] + hash->tmp32[3];
	hash->var_32[7] = hash->var_32[6];
	hash->var_32[6] = hash->var_32[5];
	hash->var_32[5] = hash->var_32[4];
	hash->var_32[4] = hash->var_32[3] + hash->t1;
	hash->var_32[3] = hash->var_32[2];
	hash->var_32[2] = hash->var_32[1];
	hash->var_32[1] = hash->var_32[0];
	hash->var_32[0] = hash->t1 + hash->t2;
}

void		sha256_hash(char *str, t_hash *hash)
{
	uint32_t	*k;
	uint32_t	*msg;
	int			j;

	sha256_init_hash(hash);
	msg = sha256_init_padding(str, hash->read, hash);
	k = sha256_init_sines();
	while (hash->offset < hash->msg_len)
	{
		if (!(hash->w32 = ft_calloc(64, sizeof(uint32_t))))
			failed_allocate_exit("Failed to allocate w\n");
		ft_memcpy(hash->w32, &msg[hash->offset * 16], 16 * sizeof(uint32_t));
		set_hash_values_for_chunk(hash);
		j = -1;
		while (++j < 64)
			sha256_bitsmess(j, k, hash);
		sha256_add_chunk(hash);
		free(hash->w32);
		hash->offset++;
	}
	free(msg);
}
