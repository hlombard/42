/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 13:38:36 by hlombard          #+#    #+#             */
/*   Updated: 2020/09/12 13:38:41 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	*md5_init_sines(void)
{
	static uint32_t k[64] = {
		0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
		0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
		0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
		0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
		0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
		0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
		0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
		0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
		0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
		0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
		0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
		0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
		0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
		0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
		0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
		0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

	return (k);
}

uint32_t	*md5_init_shift_amount(void)
{
	static uint32_t r[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
		7, 12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5,
		9, 14, 20, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11,
		16, 23, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

	return (r);
}

uint8_t		*md5_init_padding(char *str, size_t len, t_hash *hash)
{
	uint8_t		*message;
	uint32_t	size_signature;

	hash->msg_len = len * 8 + 1;
	size_signature = len * 8;
	while (hash->msg_len % 512 != 448)
		hash->msg_len++;
	hash->msg_len /= 8;
	if ((message = ft_calloc((hash->msg_len) + 64, sizeof(uint8_t))) == NULL)
		failed_allocate_exit("Failed to calloc msg\n");
	ft_memcpy(message, str, len);
	message[len] = 0x80;
	ft_memcpy(&message[hash->msg_len], &size_signature, sizeof(uint32_t));
	hash->offset = 0;
	return (message);
}

void		md5_init_hash(t_hash *hash)
{
	hash->h_32[0] = MD5_H0;
	hash->h_32[1] = MD5_H1;
	hash->h_32[2] = MD5_H2;
	hash->h_32[3] = MD5_H3;
}
