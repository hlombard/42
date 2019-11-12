/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassembler.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 17:17:25 by ratin             #+#    #+#             */
/*   Updated: 2019/09/05 02:00:38 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISASSEMBLER_H
# define DISASSEMBLER_H

# include <fcntl.h>
# include "libft.h"
# include "op.h"

# define ERROR			-1
# define SUCCESS		1

typedef struct			s_corewar
{
	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH];
	unsigned char		*code;
	unsigned int		size;
	unsigned int		magic;
	unsigned int		pc;
	int					fd;
}						t_corewar;

typedef struct			s_type
{
	int					param1;
	int					param2;
	int					param3;
}						t_type;

typedef struct			s_op
{
	char				*name;
	int					nbr_of_param;
	t_type				type_of_param;
	int					opcode;
	int					nbr_of_cycle;
	char				*description;
	unsigned int		coding_opcode;
	unsigned int		direct_size;
}						t_op;

typedef	struct			s_arg
{
	int					nb_arg;
	t_arg_type			type[4];
	unsigned int		size[4];
	unsigned int		value[4];
	int					dir_size;
	int					ocp;
}						t_arg;

/*
** PARSING
*/

uint32_t				swap_endian(uint32_t val);
void					read_process(char *name, t_corewar *cor);
void					decomp_quit(t_corewar *cor, char *str);
void					create_file(t_corewar *cor, char *name);
void					print_file(t_corewar *cor);
void					create_list(t_corewar *cor);
void					stock_process_name(t_corewar *cor, t_header *header);
void					stock_process_size(t_corewar *cor, t_header *header);
void					stock_process_code(t_corewar *cor, int fd);
void					stock_process_comment(t_corewar *cor, t_header *header);
void					stock_process_magic(t_corewar *cor, t_header *header);

/*
** INSTRUCTION
*/
void					inst_sti(t_corewar *cor);
void					inst_and(t_corewar *cor);
void					inst_live(t_corewar *cor);
void					inst_zjmp(t_corewar *cor);
void					inst_ld(t_corewar *cor);

char					*get_small_dir(t_corewar *cor);
char					*get_big_dir(t_corewar *cor);
char					*get_reg_index(t_corewar *cor);
char					*get_ind(t_corewar *cor);
char					*get_small_param(t_corewar *cor, int type);
int						*check_opcode(t_corewar *cor);
void					get_params(t_corewar *cor, t_arg *arg, int opcode);
void					ft_get_args(t_corewar *cor, t_arg *arg);

/*
** DEBUG
*/
void					print_champion(t_corewar *cor);
void					pcode(t_corewar *cor, int pc);
#endif
