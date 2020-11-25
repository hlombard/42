/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:49:54 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/31 01:41:36 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t	l_rotate64(uint64_t x, uint64_t c)
{
	return (((x) << (c)) | ((x) >> (64 - (c))));
}

uint64_t	r_rotate64(uint64_t x, uint64_t c)
{
	return (((x) >> (c)) | ((x) << (64 - c)));
}

uint64_t	reverse_endian64(uint64_t value)
{
	return ((value & 0x00000000000000FFUL) << 56
		| (value & 0x000000000000FF00UL) << 40
		| (value & 0x0000000000FF0000UL) << 24
		| (value & 0x00000000FF000000UL) << 8
		| (value & 0x000000FF00000000UL) >> 8
		| (value & 0x0000FF0000000000UL) >> 24
		| (value & 0x00FF000000000000UL) >> 40
		| (value & 0xFF00000000000000UL) >> 56);
}

uint64_t	str_to_64(unsigned char *str)
{
	uint64_t	value;
	int			i;

	value = 0;
	i = -1;
	while (++i < 8)
	{
		value <<= 8;
		value |= str[i];
	}
	return (value);
}

uint64_t	uint32_join(uint32_t value_a, uint32_t value_b)
{
	return (((uint64_t)value_a << 32) + (value_b));
}
