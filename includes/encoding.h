/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoding.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 02:20:47 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/28 13:40:19 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENCODING_H
# define ENCODING_H

# include "encoding.h"

# define FLAG_ENC_D 1
# define FLAG_ENC_E 2
# define FLAG_ENC_I 4
# define FLAG_ENC_O 8
# define FLAG_ENC_URL 16

typedef struct	s_encoding
{
	int				flags;
	char			*input_file;
	char			*output_file;
	size_t			input_len;
	size_t			output_len;
	size_t			count;
	size_t			last_3;
	int				index;
	int				enc_type;

}				t_encoding;

typedef struct	s_encoding_dispatch
{
	const char			*name;
	const char			*bigname;
	unsigned char		*(*encodefunc)(unsigned char *str, t_encoding *enc);
	unsigned char		*(*decodefunc)(unsigned char *str, t_encoding *enc);

}				t_encoding_dispatch;

unsigned char	*base64_encode(unsigned char *str, t_encoding *enc);
unsigned char	*base64_decode(unsigned char *str, t_encoding *enc);
void			enc_load(char *str, t_encoding *enc);
void			enc_flags_set(int ac, char **av, t_encoding *enc);
void			enc_manage(t_encoding *enc);
unsigned char	*enc_read_file(char *file, t_encoding *enc);

#endif
