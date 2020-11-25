/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:54:53 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/14 22:55:50 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static unsigned char	*enc_get_input(t_encoding *enc)
{
	if (!(enc->flags & FLAG_ENC_I))
		return (read_stdin(&enc->input_len));
	else
		return (read_file(enc->input_file, &enc->input_len));
}

void					enc_load(char *str, t_encoding *enc)
{
	int i;

	i = -1;
	while (g_enc[++i].name != NULL)
	{
		if (!ft_strcmp(str, g_enc[i].name))
			enc->enc_type = i;
	}
}

void					enc_manage(t_encoding *enc)
{
	unsigned char	*msg_original;
	unsigned char	*msg_new;

	if (!(msg_original = enc_get_input(enc)))
		return ;
	if (enc->flags & FLAG_ENC_E)
		msg_new = g_enc[enc->enc_type].encodefunc(msg_original, enc);
	else
		msg_new = g_enc[enc->enc_type].decodefunc(msg_original, enc);
	if (!msg_new)
		return ;
	if (enc->flags & FLAG_ENC_O)
		write_file(msg_new, enc->output_file, enc->output_len);
	else
		write_stdin(msg_new, enc->output_len);
	free(msg_new);
}
