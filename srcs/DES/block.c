/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 14:06:21 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/28 13:06:52 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t				block_extract(unsigned char *msg)
{
	uint64_t		block;
	int				i;

	i = 0;
	block = 0;
	while (i < 8)
	{
		block <<= 8;
		block |= msg[i];
		i++;
	}
	return (block);
}

uint64_t				block_encrypt(uint64_t block, t_des *des)
{
	uint64_t original;

	if (des->des_type == CBC || des->des_type == DES_DEF)
		block ^= des->iv_format;
	if (des->des_type == CBC || des->des_type == DES_DEF
	|| des->des_type == ECB)
		block = process_block(block, des->subkeys);
	if (des->des_type == CFB)
	{
		original = block;
		block = process_block(des->iv_format, des->subkeys);
		block ^= original;
	}
	if (des->des_type == CBC || des->des_type == DES_DEF
	|| des->des_type == CFB)
		des->iv_format = block;
	return (block);
}

uint64_t				block_decrypt(uint64_t block, t_des *des)
{
	uint64_t	prev_block;

	if (des->des_type == CBC || des->des_type == DES_DEF
	|| des->des_type == CFB)
		prev_block = block;
	block = process_block(block, des->subkeys);
	if (des->des_type == CBC || des->des_type == DES_DEF)
	{
		block ^= des->iv_format;
		des->iv_format = prev_block;
	}
	if (des->des_type == CFB)
	{
		block = process_block(des->iv_format, des->subkeys);
		block ^= prev_block;
		des->iv_format = prev_block;
	}
	return (block);
}

void					block_add(unsigned char *data, uint64_t block)
{
	unsigned char	c;
	int				i;

	i = 0;
	while (i < 8)
	{
		c = (block >> (56 - (i * 8))) & 0xff;
		data[i] = c;
		i++;
	}
}
