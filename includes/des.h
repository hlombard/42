/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 10:33:48 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/31 01:10:22 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_H
# define DES_H

# include <time.h>

# define FLAG_DES_E 1
# define FLAG_DES_D 2
# define FLAG_DES_I 4
# define FLAG_DES_O 8
# define FLAG_DES_K 16
# define FLAG_DES_A 32
# define FLAG_DES_P 64
# define FLAG_DES_S 128
# define FLAG_DES_V 256
# define FLAG_DES_P_MAJ 512
# define FLAG_DES_NOPAD 1024

# define DES_DEF 0
# define ECB 1
# define CBC 2
# define CFB 3

# define MD5 0

typedef struct			s_des
{
	int				flags;
	int				des_type;
	char			*input_file;
	char			*output_file;
	char			*key;
	char			*salt_str;
	char			*iv;
	char			*pass;
	size_t			new_len;
	size_t			header_len;

	uint64_t		salt_format;
	uint64_t		iv_format;
	uint64_t		key_format;
	uint64_t		subkeys[16];

}						t_des;

typedef struct			s_des_dispatch
{
	const char			*name;
	const char			*bigname;
	unsigned char		*(*encrypt)(unsigned char *msg_original,
						size_t size, t_des *des);
	unsigned char		*(*decrypt)(unsigned char *msg_original,
						size_t size, t_des *des);

}						t_des_dispatch;

extern unsigned char g_p[32];

int						des_flags_set(int ac, char **av, t_des *des);
void					get_data_and_check(t_des *des);
void					des_load(char *str, t_des *des);
void					des_manage(t_des *des);
unsigned char			*des_decrypt(unsigned char *msg_original,
						size_t len, t_des *des);
uint64_t				process_block(uint64_t block, uint64_t subkeys[16]);
uint64_t				block_extract(unsigned char *msg);
uint64_t				block_encrypt(uint64_t block, t_des *des);
uint64_t				block_decrypt(uint64_t block, t_des *des);
void					block_add(unsigned char *data, uint64_t block);
unsigned char			*des_encrypt(unsigned char *msg_original,
						size_t len, t_des *des);
void					des_padd_add(size_t *size, size_t new_size,
						unsigned char *msg_new);
void					key_get_format(t_des *des);
void					create_subkeys(t_des *des, int encrypt);
uint64_t				get_salt(t_des *des);
uint64_t				hex_str_to_64(char *str);
uint64_t				permute_bits_from_table(uint64_t key, uint8_t *array,
						int size, int newsize);
unsigned char			*msg_decode_b64(unsigned char *msg, size_t *size);
unsigned char			*msg_encode_b64(unsigned char *msg, size_t *size);
unsigned char			*msg_with_header(t_des *des, unsigned char *msg_new);
void					free_quit_pass(t_des *des, char *str);
void					free_quit_checkdata(t_des *des, char *str);
void					free_needed(t_des *des);

#endif
