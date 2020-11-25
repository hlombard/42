/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 23:07:46 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/29 09:35:02 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t				hex_str_to_64(char *str)
{
	char				uppercase[16];
	int					i;
	uint64_t			nb;

	if (str == NULL)
		return (0);
	nb = 0;
	i = 0;
	while (str[i] == ' ')
		i++;
	while (nb < 16)
		uppercase[nb++] = str[i] ? ft_toupper(str[i++]) : '0';
	uppercase[nb] = '\0';
	nb = 0;
	i = 0;
	while (ft_hexdigit(uppercase[i]))
	{
		nb *= 16;
		nb += ft_isdigit(uppercase[i]) ?
			(uppercase[i++] - '0') : (10 + (uppercase[i++] - 'A'));
	}
	return (nb);
}

uint64_t				permute_bits_from_table(uint64_t key, uint8_t *array,
					int size, int newsize)
{
	uint64_t		ret;
	int				i;

	i = 0;
	ret = 0;
	while (i < newsize)
	{
		ret |= (((key >> (size - array[i])) % 2) << (newsize - 1 - i));
		i++;
	}
	return (ret);
}

unsigned char			*msg_decode_b64(unsigned char *msg, size_t *size)
{
	t_encoding		enc;
	unsigned char	*new;

	ft_bzero(&enc, sizeof(t_encoding));
	enc.input_len = *size;
	new = base64_decode(msg, &enc);
	if (!new)
	{
		free(msg);
		exit(EXIT_FAILURE);
	}
	*size = enc.output_len;
	return (new);
}

unsigned char			*msg_encode_b64(unsigned char *msg, size_t *size)
{
	t_encoding		enc;
	unsigned char	*new;

	ft_bzero(&enc, sizeof(t_encoding));
	enc.input_len = *size;
	if (!(new = base64_encode(msg, &enc)))
	{
		free(msg);
		exit(EXIT_FAILURE);
	}
	*size = enc.output_len;
	return (new);
}

unsigned char			*msg_with_header(t_des *des, unsigned char *msg_new)
{
	unsigned char	*header;
	unsigned char	*header_msg;
	uint64_t		salt_value;

	if (!(header = ft_memalloc(16 + 1)))
		exit(EXIT_FAILURE);
	des->new_len += 16;
	ft_memcpy(header, "Salted__", 8);
	salt_value = reverse_endian64(des->salt_format);
	ft_memcpy(&header[8], &salt_value, 8);
	header_msg = ft_memalloc(des->new_len + 16);
	ft_memcpy(header_msg, header, 16);
	ft_memcpy(&header_msg[16], msg_new, des->new_len);
	free(header);
	free(msg_new);
	return (header_msg);
}
