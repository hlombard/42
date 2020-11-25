/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:11:17 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/31 00:54:24 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			des_load(char *str, t_des *des)
{
	int i;

	i = -1;
	while (g_des[++i].name != NULL)
	{
		if (!ft_strcmp(str, g_des[i].name))
			des->des_type = i;
	}
}

void			des_manage(t_des *des)
{
	unsigned char	*msg_original;
	unsigned char	*msg_new;
	size_t			size;

	size = 0;
	get_data_and_check(des);
	msg_original = !des->input_file ?
		read_stdin(&size) : read_file(des->input_file, &size);
	if (!msg_original)
		exit(EXIT_FAILURE);
	if (des->flags & FLAG_DES_D && des->flags & FLAG_DES_A)
		msg_original = msg_decode_b64(msg_original, &size);
	if (des->flags & FLAG_DES_E)
		msg_new = g_des[des->des_type].encrypt(msg_original, size, des);
	else
		msg_new = g_des[des->des_type].decrypt(msg_original, size, des);
	if (!msg_new)
		exit(EXIT_FAILURE);
	if (des->flags & FLAG_DES_E && des->flags & FLAG_DES_A)
		msg_new = msg_encode_b64(msg_new, &des->new_len);
	des->output_file ? write_file(msg_new, des->output_file, des->new_len)
		: write_stdin(msg_new, des->new_len);
	free(msg_new);
}
