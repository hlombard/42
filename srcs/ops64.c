/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 13:43:02 by hlombard          #+#    #+#             */
/*   Updated: 2020/09/12 13:43:17 by hlombard         ###   ########.fr       */
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