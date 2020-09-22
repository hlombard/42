/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 13:45:21 by hlombard          #+#    #+#             */
/*   Updated: 2020/09/16 12:31:59 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t	*sha512_init_padding(char *str, size_t len, t_hash *hash)
{
	uint64_t	*message;
	int			i;

	hash->msg_len = len * 8 + 1;
	while (hash->msg_len % 1024 != 896)
		hash->msg_len++;
	hash->msg_len = (hash->msg_len + 128) / 1024;
	if (!(message = ft_calloc(hash->msg_len, 1024)))
		failed_allocate_exit("Failed to calloc msg\n");
	ft_memcpy(message, str, len);
	((uint8_t*)message)[len] = 0x80;
	i = -1;
	while (++i < (int)len + 1)
		message[i] = reverse_endian64(message[i]);
	message[((hash->msg_len * 1024 - 128) / 64) + 1] = len * 8;
	hash->offset = 0;
	return (message);
}

void		sha512_init_hash(t_hash *hash)
{
	if (!ft_strcmp(g_hash[hash->algo_type].name, "sha512"))
	{
		hash->h_64[0] = SHA512_H0;
		hash->h_64[1] = SHA512_H1;
		hash->h_64[2] = SHA512_H2;
		hash->h_64[3] = SHA512_H3;
		hash->h_64[4] = SHA512_H4;
		hash->h_64[5] = SHA512_H5;
		hash->h_64[6] = SHA512_H6;
		hash->h_64[7] = SHA512_H7;
	}
	else
	{
		hash->h_64[0] = SHA384_H0;
		hash->h_64[1] = SHA384_H1;
		hash->h_64[2] = SHA384_H2;
		hash->h_64[3] = SHA384_H3;
		hash->h_64[4] = SHA384_H4;
		hash->h_64[5] = SHA384_H5;
		hash->h_64[6] = SHA384_H6;
		hash->h_64[7] = SHA384_H7;
	}
}
