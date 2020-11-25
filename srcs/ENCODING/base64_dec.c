/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_dec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:59:13 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/31 00:45:19 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static unsigned char g_b64_decode[256] = {
	80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,
	80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,
	80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 62, 80, 80, 80, 63,
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 80, 80, 80, 80, 80, 80,
	80, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 80, 80, 80, 80, 80,
	80, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
	41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 80, 80, 80, 80, 80,
	80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,
	80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,
	80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,
	80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,
	80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,
	80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,
	80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,
	80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80 };

static unsigned char	*base64_decode_init(unsigned char *str,
								t_encoding *enc)
{
	unsigned char *ret;

	enc->output_len = 0;
	if (enc->input_len % 4 != 0)
		return (NULL);
	enc->output_len = (enc->input_len / 4) * 3;
	if (str[enc->input_len - 1] == '=')
		enc->output_len--;
	if (str[enc->input_len - 2] == '=')
		enc->output_len--;
	ret = (unsigned char *)ft_strnew(enc->output_len + 1);
	enc->index = 0;
	return (ret);
}

static void				base64_remove_whitespaces(unsigned char *input,
								t_encoding *enc)
{
	size_t			i;
	size_t			j;

	i = 0;
	j = 0;
	while (j < enc->input_len)
	{
		if (is_whitespace(input[j]))
			j++;
		else
			input[i++] = input[j++];
	}
	enc->input_len = i;
}

unsigned char			*base64_decode(unsigned char *str, t_encoding *enc)
{
	unsigned char	*decoded;
	unsigned char	byte[4];
	size_t			i;

	base64_remove_whitespaces(str, enc);
	if (!(decoded = base64_decode_init(str, enc)))
		return (NULL);
	i = 0;
	while (i < enc->input_len)
	{
		byte[0] = g_b64_decode[(unsigned char)str[i++]];
		byte[1] = g_b64_decode[(unsigned char)str[i++]];
		byte[2] = g_b64_decode[(unsigned char)str[i++]];
		byte[3] = g_b64_decode[(unsigned char)str[i++]];
		decoded[enc->index++] = (byte[0] << 2 | ((byte[1] & 0xF0) >> 4));
		decoded[enc->index++] = (((byte[1] & 0x0F) << 4)
		| ((byte[2] & 0x3C) >> 2));
		decoded[enc->index++] = (((byte[2] & 0x03) << 6) | (byte[3] & 0x3F));
	}
	free(str);
	return (decoded);
}
