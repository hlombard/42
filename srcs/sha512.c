/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 13:49:43 by hlombard          #+#    #+#             */
/*   Updated: 2020/09/14 19:31:03 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static uint64_t g_k[] = {
	0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f,
	0xe9b5dba58189dbbc, 0x3956c25bf348b538, 0x59f111f1b605d019,
	0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242,
	0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
	0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235,
	0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
	0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65, 0x2de92c6f592b0275,
	0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
	0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f,
	0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725,
	0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc,
	0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
	0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6,
	0x92722c851482353b, 0xa2bfe8a14cf10364, 0xa81a664bbc423001,
	0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218,
	0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99,
	0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
	0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc,
	0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915,
	0xc67178f2e372532b, 0xca273eceea26619c, 0xd186b8c721c0c207,
	0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba,
	0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
	0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
	0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
	0x5fcb6fab3ad6faec, 0x6c44198c4a475817 };

static void	set_hash_values_for_chunk(t_hash *hash)
{
	int round;

	round = 16;
	while (round < 80)
	{
		hash->tmp64[0] = r_rotate64(hash->w64[round - 15], 1) ^
			r_rotate64(hash->w64[round - 15], 8) ^ (hash->w64[round - 15] >> 7);
		hash->tmp64[1] = r_rotate64(hash->w64[round - 2], 19) ^
			r_rotate64(hash->w64[round - 2], 61) ^ (hash->w64[round - 2] >> 6);
		hash->w64[round] = hash->w64[round - 16] + hash->tmp64[0] +
			hash->w64[round - 7] + hash->tmp64[1];
		round++;
	}
	hash->var_64[0] = hash->h_64[0];
	hash->var_64[1] = hash->h_64[1];
	hash->var_64[2] = hash->h_64[2];
	hash->var_64[3] = hash->h_64[3];
	hash->var_64[4] = hash->h_64[4];
	hash->var_64[5] = hash->h_64[5];
	hash->var_64[6] = hash->h_64[6];
	hash->var_64[7] = hash->h_64[7];
}

static void	sha512_bitsmess(int j, t_hash *hash)
{
	hash->tmp64[1] = r_rotate64(hash->var_64[4], 14) ^
	r_rotate64(hash->var_64[4], 18) ^ r_rotate64(hash->var_64[4], 41);
	hash->tmp64[2] = (hash->var_64[4] & hash->var_64[5]) ^
	((~hash->var_64[4]) & hash->var_64[6]);
	hash->t3 = hash->var_64[7] + hash->tmp64[1] + hash->tmp64[2] +
	g_k[j] + hash->w64[j];
	hash->tmp64[0] = r_rotate64(hash->var_64[0], 28) ^
	r_rotate64(hash->var_64[0], 34) ^ r_rotate64(hash->var_64[0], 39);
	hash->tmp64[3] = (hash->var_64[0] & hash->var_64[1]) ^
	(hash->var_64[0] & hash->var_64[2]) ^ (hash->var_64[1] & hash->var_64[2]);
	hash->t4 = hash->tmp64[0] + hash->tmp64[3];
	hash->var_64[7] = hash->var_64[6];
	hash->var_64[6] = hash->var_64[5];
	hash->var_64[5] = hash->var_64[4];
	hash->var_64[4] = hash->var_64[3] + hash->t3;
	hash->var_64[3] = hash->var_64[2];
	hash->var_64[2] = hash->var_64[1];
	hash->var_64[1] = hash->var_64[0];
	hash->var_64[0] = hash->t3 + hash->t4;
}

static void	sha512_add_chunk(t_hash *hash)
{
	hash->h_64[0] += hash->var_64[0];
	hash->h_64[1] += hash->var_64[1];
	hash->h_64[2] += hash->var_64[2];
	hash->h_64[3] += hash->var_64[3];
	hash->h_64[4] += hash->var_64[4];
	hash->h_64[5] += hash->var_64[5];
	hash->h_64[6] += hash->var_64[6];
	hash->h_64[7] += hash->var_64[7];
}

void		sha512_hash(char *str, t_hash *hash)
{
	int			j;
	uint64_t	*msg;

	sha512_init_hash(hash);
	msg = sha512_init_padding(str, hash->read, hash);
	while (hash->offset < hash->msg_len)
	{
		if (!(hash->w64 = ft_calloc(80, sizeof(uint64_t))))
			failed_allocate_exit("Failed to allocate w\n");
		ft_memcpy(hash->w64, &msg[hash->offset * 16], 16 * sizeof(uint64_t));
		set_hash_values_for_chunk(hash);
		j = -1;
		while (++j < 80)
			sha512_bitsmess(j, hash);
		sha512_add_chunk(hash);
		free(hash->w64);
		hash->offset++;
	}
	free(msg);
}
