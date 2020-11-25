/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_decrypt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:07:14 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/31 19:29:52 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void				free_quit_decrypt(unsigned char *str)
{
	ft_putstr_fd("bad decrypt\n", 2);
	free(str);
	exit(EXIT_FAILURE);
}

static void				des_padd_remove(size_t *size, unsigned char *msg_new,
					t_des *des)
{
	size_t			new_size;
	unsigned char	c;

	c = msg_new[*size - 1];
	if (c >= 1 && c <= 8)
	{
		new_size = *size - c;
		while (msg_new[new_size] == c && new_size < *size)
			new_size++;
		if (new_size == *size)
			*size -= c;
		else
			free_quit_decrypt(msg_new);
	}
	else
		free_quit_decrypt(msg_new);
	des->new_len = *size;
}

static unsigned char	*init_msg_decrypt(unsigned char *msg_original,
						size_t *len, size_t *i, t_des *des)
{
	unsigned char *msg_new;

	*len -= des->header_len;
	if (!(msg_new = ft_memalloc(((*len / 8) + 1) * 8 + 1)))
		exit(EXIT_FAILURE);
	*i = 0;
	ft_memcpy(msg_new, &msg_original[des->header_len], *len);
	free(msg_original);
	des->new_len = *len;
	return (msg_new);
}

unsigned char			*des_decrypt(unsigned char *msg_original,
						size_t len, t_des *des)
{
	size_t			i;
	uint64_t		block;
	unsigned char	*msg_new;

	msg_new = init_msg_decrypt(msg_original, &len, &i, des);
	while (i < len)
	{
		block = block_extract(&msg_new[i]);
		block = block_decrypt(block, des);
		block_add(&msg_new[i], block);
		i += sizeof(block);
	}
	if (des->des_type != CFB)
		des_padd_remove(&len, msg_new, des);
	return (msg_new);
}
