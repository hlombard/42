/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 02:20:47 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/31 01:34:12 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"
# include "ft_printf.h"
# include "encoding.h"
# include "des.h"
# include "hash.h"
# include <fcntl.h>
# include <errno.h>

# define HASH		1
# define DES		2
# define ENCODING	3

# define BUFFSIZE 1024

extern	t_des_dispatch	g_des[];
extern	t_encoding_dispatch	g_enc[];
extern	t_hash_dispatch	g_hash[];

void				command_start_hash(int argc, char **argv, t_hash *hash);
void				command_start_des(int argc, char **argv, t_des *des);
void				command_start_encoding(int argc, char **argv,
					t_encoding *encoding);
int					command_check(int ac, char **av);

void				failed_allocate_exit(char *str);
void				error_command(char *str);

unsigned char		*read_stdin(size_t *size);
unsigned char		*read_file(char *file, size_t *size);
unsigned char		*read_n_chars(t_des *des, size_t len);

void				write_file(unsigned char *content, char *output_file,
					size_t output_len);
void				write_stdin(unsigned char *content, size_t output_len);

uint32_t			l_rotate32(uint32_t x, uint32_t c);
uint32_t			r_rotate32(uint32_t x, uint32_t c);
uint32_t			reverse_endian32(uint32_t value);

uint64_t			reverse_endian64(uint64_t value);
uint64_t			l_rotate64(uint64_t x, uint64_t c);
uint64_t			r_rotate64(uint64_t x, uint64_t c);
uint64_t			str_to_64(unsigned char *str);
uint64_t			uint32_join(uint32_t value_a, uint32_t value_b);

#endif
