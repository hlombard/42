/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_encrypt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:08:26 by hlombard          #+#    #+#             */
/*   Updated: 2020/11/01 00:54:33 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static uint8_t g_s_boxes[8][64] = {
	{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7, 0, 15, 7, 4, 14, 2,
		13, 1, 10, 6, 12, 11, 9, 5, 3, 8, 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9,
		7, 3, 10, 5, 0, 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
	{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10, 3, 13, 4, 7, 15, 2,
		8, 14, 12, 0, 1, 10, 6, 9, 11, 5, 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12,
		6, 9, 3, 2, 15, 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
	{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8, 13, 7, 0, 9, 3, 4, 6,
		10, 2, 8, 5, 14, 12, 11, 15, 1, 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12,
		5, 10, 14, 7, 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
	{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15, 13, 8, 11, 5, 6, 15,
		0, 3, 4, 7, 2, 12, 1, 10, 14, 9, 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3,
		14, 5, 2, 8, 4, 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
	{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9, 14, 11, 2, 12, 4, 7,
		13, 1, 5, 0, 15, 10, 3, 9, 8, 6, 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12,
		5, 6, 3, 0, 14, 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
	{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11, 10, 15, 4, 2, 7, 12,
		9, 5, 6, 1, 13, 14, 0, 11, 3, 8, 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10,
		1, 13, 11, 6, 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
	{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1, 13, 0, 11, 7, 4, 9,
		1, 10, 14, 3, 5, 12, 2, 15, 8, 6, 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6,
		8, 0, 5, 9, 2, 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
	{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7, 1, 15, 13, 8, 10, 3,
		7, 4, 12, 5, 6, 11, 0, 14, 9, 2, 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10,
		13, 15, 3, 5, 8, 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}};

static unsigned char	g_ebit[] = {
	32, 1, 2, 3, 4, 5,
	4, 5, 6, 7, 8, 9,
	8, 9, 10, 11, 12, 13,
	12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21,
	20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29,
	28, 29, 30, 31, 32, 1};

static unsigned char	g_ip2[] = {
	40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41, 9, 49, 17, 57, 25};

static uint8_t g_ip1[] = {58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20,
	12, 4, 62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8, 57, 49,
	41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3, 61, 53, 45, 37, 29, 21,
	13, 5, 63, 55, 47, 39, 31, 23, 15, 7};

static uint64_t			s_box_value(uint64_t nb, int i)
{
	uint64_t	value_6_bits;
	int			col;
	int			row;

	value_6_bits = (nb >> (42 - (i * 6))) & 0x3f;
	row = ((value_6_bits >> 5) << 1) + (value_6_bits & 1);
	col = (value_6_bits >> 1) & 0xf;
	return (g_s_boxes[i][row * 16 + col]);
}

static uint64_t			reduce_to_32(uint64_t nb)
{
	uint64_t	value_4_bits;
	uint64_t	result;
	int			i;

	i = -1;
	result = 0;
	while (++i < 8)
	{
		value_4_bits = s_box_value(nb, i);
		result <<= 4;
		result += value_4_bits;
	}
	return (result);
}

uint64_t				process_block(uint64_t block, uint64_t subkeys[16])
{
	uint64_t	left;
	uint64_t	right;
	uint64_t	pblock;
	uint64_t	right_next;
	int			i;

	pblock = permute_bits_from_table(block, g_ip1, 64, 64);
	left = (pblock >> 32) & 0xffffffff;
	right = pblock & 0xffffffff;
	i = -1;
	while (++i < 16)
	{
		pblock = reduce_to_32(permute_bits_from_table(right, g_ebit, 32, 48)
		^ subkeys[i]);
		right_next = left ^ permute_bits_from_table(pblock, g_p, 32, 32);
		left = right;
		right = right_next;
	}
	return (permute_bits_from_table((right_next << 32) + left, g_ip2, 64, 64));
}

void					des_padd_add(size_t *size, size_t new_size,
						unsigned char *msg_new)
{
	unsigned char	c;

	c = new_size - *size;
	while (*size < new_size)
		msg_new[(*size)++] = c;
}

unsigned char			*des_encrypt(unsigned char *msg_original,
						size_t len, t_des *des)
{
	size_t			i;
	uint64_t		block;
	unsigned char	*msg_new;

	des->new_len = (des->flags & FLAG_DES_NOPAD || des->des_type == CFB)
	? len : ((len / 8) + 1) * 8;
	if ((msg_new = ft_memalloc(des->new_len + 1)) == NULL)
		exit(EXIT_FAILURE);
	ft_memcpy(msg_new, msg_original, len);
	free(msg_original);
	des_padd_add(&len, des->new_len, msg_new);
	i = 0;
	while (i < len)
	{
		block = block_extract(&msg_new[i]);
		block = block_encrypt(block, des);
		block_add(&msg_new[i], block);
		i += sizeof(block);
	}
	if ((!des->key) || (des->key && des->des_type != ECB && !des->iv))
		return (msg_with_header(des, msg_new));
	return (msg_new);
}
