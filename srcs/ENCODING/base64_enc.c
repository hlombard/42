/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_enc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:56:13 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/28 13:52:13 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static unsigned char g_b64_table[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz0123456789+/";

static void					base64_encode_init(t_encoding *enc)
{
	enc->output_len = (((enc->input_len + 2) / 3) * 4);
	enc->last_3 = (enc->input_len / 3) * 3;
	enc->count = 0;
	enc->index = 0;
	if (enc->flags & FLAG_ENC_URL)
	{
		g_b64_table[62] = '-';
		g_b64_table[63] = '_';
	}
}

static void					base64_padding(unsigned char *encoded,
			unsigned char *str, t_encoding *enc)
{
	encoded[enc->index++] = g_b64_table[(str[enc->count] >> 2) & 0x3F];
	if (enc->count == enc->input_len - 1)
	{
		encoded[enc->index++] = g_b64_table[(str[enc->count] & 0x3) << 4];
		encoded[enc->index++] = '=';
		if (enc->flags & FLAG_ENC_URL)
		{
			encoded[enc->index - 1] = '\0';
			enc->output_len--;
		}
	}
	else
	{
		encoded[enc->index++] = g_b64_table[(str[enc->count] & 0x3) << 4
			| (str[enc->count + 1] & 0xF0) >> 4];
		encoded[enc->index++] = g_b64_table[(str[enc->count + 1] & 0xF) << 2];
	}
	encoded[enc->index++] = '=';
	if (enc->flags & FLAG_ENC_URL)
	{
		encoded[enc->index - 1] = '\0';
		enc->output_len--;
	}
}

static unsigned char		*base64_add_newlines(unsigned char *input,
							t_encoding *enc)
{
	size_t			i;
	size_t			j;
	unsigned char	*reformated;

	enc->output_len = enc->output_len + (enc->output_len / 64);
	if ((reformated = ft_memalloc(enc->output_len + 1)) == NULL)
		exit(EXIT_FAILURE);
	i = 0;
	j = 0;
	while (i < enc->output_len)
	{
		reformated[i++] = (input)[j++];
		if (j % 64 == 0)
			reformated[i++] = '\n';
	}
	if (reformated[enc->output_len - 1] != '\n')
		reformated[enc->output_len++] = '\n';
	free(input);
	return (reformated);
}

unsigned char				*base64_encode(unsigned char *str, t_encoding *enc)
{
	unsigned char			*encoded;

	if (enc->input_len < 1)
		return (NULL);
	base64_encode_init(enc);
	if (!(encoded = (unsigned char *)ft_strnew(enc->output_len)))
		return (NULL);
	while (enc->count < enc->last_3)
	{
		encoded[enc->index++] = g_b64_table[str[enc->count] >> 2];
		encoded[enc->index++] = g_b64_table[(str[enc->count] & 0x03) << 4
		| (str[enc->count + 1] & 0xf0) >> 4];
		encoded[enc->index++] = g_b64_table[(str[enc->count + 1] & 0x0F) << 2
		| (str[enc->count + 2] & 0xC0) >> 6];
		encoded[enc->index++] = g_b64_table[(str[enc->count + 2] & 0X3F)];
		enc->count += 3;
	}
	if (enc->count < enc->input_len)
		base64_padding(encoded, str, enc);
	encoded = base64_add_newlines(encoded, enc);
	free(str);
	return (encoded);
}
