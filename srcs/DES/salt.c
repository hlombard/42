/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   salt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:43:21 by hlombard          #+#    #+#             */
/*   Updated: 2020/11/01 00:58:20 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static char				*get_random_salt(void)
{
	const char	*hex_digit = "0123456789ABCDEF";
	int			i;
	char		c;
	char		*salt_random;

	if (!(salt_random = ft_strnew(16 + 1)))
		exit(EXIT_FAILURE);
	i = 0;
	srand(time(NULL));
	while (i < 16)
	{
		c = hex_digit[rand() % 16];
		salt_random[i++] = c;
	}
	salt_random[i] = '\0';
	return (salt_random);
}

static uint64_t			salt_decode_from_input_b64(t_des *des,
						unsigned char *msg_original, size_t len)
{
	t_encoding		enc;
	unsigned char	*msg_new;
	uint64_t		salt;

	enc.input_len = len;
	msg_new = base64_decode(msg_original, &enc);
	if (!msg_new)
	{
		free_needed(des);
		failed_allocate_exit("error reading input file\n");
	}
	if (ft_strncmp((char*)msg_new, "Salted__", 8))
	{
		free(msg_new);
		free_needed(des);
		failed_allocate_exit("bad magic number\n");
	}
	salt = str_to_64(&msg_new[8]);
	free(msg_new);
	return (salt);
}

static uint64_t			salt_decode_from_input(t_des *des, unsigned char *str)
{
	uint64_t salt;

	if (ft_strncmp((char*)str, "Salted__", 8))
	{
		free(str);
		free_needed(des);
		failed_allocate_exit("bad magic number\n");
	}
	salt = str_to_64(&str[8]);
	free(str);
	return (salt);
}

static uint64_t			get_salt_from_file(t_des *des)
{
	unsigned char	*tmp;
	size_t			len;
	uint64_t		salt;

	len = 32;
	if (!(tmp = read_n_chars(des, len)))
	{
		ft_dprintf(2, "Can't open %s for reading, %s", des->input_file,
			strerror(errno));
		free_needed(des);
		exit(EXIT_FAILURE);
	}
	if (des->flags & FLAG_DES_A)
		salt = salt_decode_from_input_b64(des, tmp, len);
	else
		salt = salt_decode_from_input(des, tmp);
	if (des->input_file)
		des->header_len = 16;
	return (salt);
}

uint64_t				get_salt(t_des *des)
{
	if (des->flags & FLAG_DES_D &&
	((!des->key) || (des->key && des->des_type != ECB && !des->iv)))
		return (get_salt_from_file(des));
	else
	{
		if (des->key || !des->salt_str)
		{
			if (des->des_type != ECB && des->key && des->pass && des->salt_str)
				return (hex_str_to_64(des->salt_str));
			des->salt_str = get_random_salt();
			return (hex_str_to_64(des->salt_str));
		}
		else
			return (hex_str_to_64(des->salt_str));
	}
}
