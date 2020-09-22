/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 02:20:47 by hlombard          #+#    #+#             */
/*   Updated: 2020/09/16 12:35:42 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "libft.h"
# include "ft_printf.h"
# include "constants.h"
# include <fcntl.h>
# include <errno.h>

# define FLAG_P 1
# define FLAG_Q 2
# define FLAG_R 4
# define FLAG_S 8

typedef struct		s_hash
{
	char			flags;
	int				flag_p;
	int				flag_s_pos;
	int				no_file;
	int				read;
	int				arg_index;
	int				print_quotes;
	int				algo_type;
	size_t			offset;
	size_t			msg_len;

	uint32_t		*w32;
	uint32_t		var_32[8];
	uint32_t		h_32[8];
	uint32_t		tmp32[4];
	uint32_t		t1;
	uint32_t		t2;

	uint64_t		*w64;
	uint64_t		var_64[8];
	uint64_t		h_64[8];
	uint64_t		tmp64[4];
	uint64_t		t3;
	uint64_t		t4;

}					t_hash;

typedef struct		s_dispatch
{
	const char	*name;
	const char	*bigname;
	void		(*hashfunc)(char *str, t_hash *hash);
	void		(*printfunc)(char *str, t_hash *hash);

}					t_dispatch;

extern				t_dispatch g_hash[];

void				quit_s_option_error(t_hash *hash);
void				failed_allocate_exit(char *str);
void				error_stdin(t_hash *hash, char *str);
void				error_command(char *str);
const char			*get_name(int type, t_hash *hash);

uint32_t			l_rotate32(uint32_t x, uint32_t c);
uint32_t			r_rotate32(uint32_t x, uint32_t c);
uint32_t			reverse_endian32(uint32_t value);

uint64_t			reverse_endian64(uint64_t value);
uint64_t			l_rotate64(uint64_t x, uint64_t c);
uint64_t			r_rotate64(uint64_t x, uint64_t c);

int					args_check(int ac, char **av, t_hash *hash);
void				args_process(char *str, char **argv, t_hash *hash);
void				args_process_s(char **argv, t_hash *hash);

void				flags_set(int ac, char **av, int i, t_hash *hash);
int					flags_p_special(t_hash *hash);
int					flags_set_q_r(char **av, t_hash *hash);
void				flags_available(void);

char				*read_stdin(t_hash *hash);
char				*read_file(char *file, t_hash *hash);
void				read_input(char *str, t_hash *hash);

void				print_md5(char *name, t_hash *hash);
void				print_sha256(char *name, t_hash *hash);
void				print_sha512(char *name, t_hash *hash);

void				md5_hash(char *str, t_hash *hash);
uint32_t			*md5_init_sines(void);
uint32_t			*md5_init_shift_amount(void);
void				md5_init_hash(t_hash *hash);
uint8_t				*md5_init_padding(char *str, size_t len, t_hash *hash);

void				sha256_init_hash(t_hash *hash);
uint32_t			*sha256_init_padding(char *str, size_t len, t_hash *hash);
uint32_t			*sha256_init_sines(void);
void				sha256_hash(char *str, t_hash *hash);

void				sha512_init_hash(t_hash *hash);
uint64_t			*sha512_init_padding(char *str, size_t len, t_hash *hash);
void				sha512_hash(char *str, t_hash *hash);

#endif
