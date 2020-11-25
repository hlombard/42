/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 02:20:47 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/23 00:59:05 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H

# define FLAG_HASH_P 1
# define FLAG_HASH_Q 2
# define FLAG_HASH_R 4
# define FLAG_HASH_S 8

/*
** ALGOS INITIALIZATION VALUES
*/

# define MD5_H0 0x67452301
# define MD5_H1 0xefcdab89
# define MD5_H2 0x98badcfe
# define MD5_H3 0x10325476

# define SHA224_H0 0xc1059ed8
# define SHA224_H1 0x367cd507
# define SHA224_H2 0x3070dd17
# define SHA224_H3 0xf70e5939
# define SHA224_H4 0xffc00b31
# define SHA224_H5 0x68581511
# define SHA224_H6 0x64f98fa7
# define SHA224_H7 0xbefa4fa4

# define SHA256_H0 0x6a09e667
# define SHA256_H1 0xbb67ae85
# define SHA256_H2 0x3c6ef372
# define SHA256_H3 0xa54ff53a
# define SHA256_H4 0x510e527f
# define SHA256_H5 0x9b05688c
# define SHA256_H6 0x1f83d9ab
# define SHA256_H7 0x5be0cd19

# define SHA384_H0 0xcbbb9d5dc1059ed8
# define SHA384_H1 0x629a292a367cd507
# define SHA384_H2 0x9159015a3070dd17
# define SHA384_H3 0x152fecd8f70e5939
# define SHA384_H4 0x67332667ffc00b31
# define SHA384_H5 0x8eb44a8768581511
# define SHA384_H6 0xdb0c2e0d64f98fa7
# define SHA384_H7 0x47b5481dbefa4fa4

# define SHA512_H0 0x6a09e667f3bcc908
# define SHA512_H1 0xbb67ae8584caa73b
# define SHA512_H2 0x3c6ef372fe94f82b
# define SHA512_H3 0xa54ff53a5f1d36f1
# define SHA512_H4 0x510e527fade682d1
# define SHA512_H5 0x9b05688c2b3e6c1f
# define SHA512_H6 0x1f83d9abfb41bd6b
# define SHA512_H7 0x5be0cd19137e2179

typedef struct		s_hash
{
	char			flags;
	int				flag_p;
	int				flag_s_pos;
	int				no_file;
	int				arg_index;
	int				print_quotes;
	int				hash_type;
	size_t			offset;
	size_t			msg_len;
	size_t			read;

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

typedef struct		s_hash_dispatch
{
	const char	*name;
	const char	*bigname;
	void		(*hashfunc)(char *str, t_hash *hash);
	void		(*printfunc)(char *str, t_hash *hash);

}					t_hash_dispatch;

void				hash_loop(int argc, char **argv, t_hash *hash);
void				hash_load(char *str, t_hash *hash);

void				quit_s_option_error(t_hash *hash);
void				error_stdin(t_hash *hash, char *str);
const char			*get_name(int type, t_hash *hash);

void				hash_flags_set(int ac, char **av, int i, t_hash *hash);
int					flags_p_special(t_hash *hash);
int					flags_set_q_r(char **av, t_hash *hash);
void				flags_available(void);

char				*hash_read_file(char *file, t_hash *hash);
void				hash_read_input(char *str, t_hash *hash);

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
