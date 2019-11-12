/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 20:20:52 by ratin             #+#    #+#             */
/*   Updated: 2019/09/05 17:33:56 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <fcntl.h>
# include "struct.h"
# include "libft.h"

# define ERROR				-1
# define SUCCESS			1

/*
** asm parsing
*/
void		get_comment(t_asm *asmbly, char *str);
void		get_name(t_asm *asmbly, char *str);
void		count_size(t_asm *asmbly);
int			parse_file(t_asm *asmbly, char *file);
int			check_comment(char *str);
int			name_presence(char *str);
int			comment_presence(char *str);
int			is_empty(t_asm *asmbly, char *str);
int			check_label_presence(char *str);
void		dlt_lst_empty_lbl(t_asm *asmbly);
int			check_opc_presence(char *str);
void		verify_label(t_asm *asmbly, char *label, int line, char *str);
int			error_type(t_asm *asmbly, t_param *param, char *str);
void		print_error(t_asm *asmbly, char *str);
void		p_error(t_asm *asmbly, t_param *param, int line, t_instru *ins);
void		free_quit_prog(t_asm *asmbly, char *str, int type);
void		add_free_param(t_asm *asmbly, t_instru **instru, int line
			, char **param);

/*
** instruction
*/
t_instru	*find_instru(t_asm *asmbly, int line);
t_instru	*get_last_instru(t_asm *asmbly);
void		get_instruction(t_asm *asmbly, char *str, int line);
void		add_instru(t_asm *asmbly, int line);
void		delete_instru(t_instru **instru);
int			get_params(t_asm *asmbly, char *str, int line);
void		check_params_error(t_asm *asmbly, char *str, int line);
void		print_erro_param(t_asm *asmbly, char *str, int line, int error);
int			get_params_type(t_asm *asmbly, char *str, int line);
void		add_param(t_asm *asmbly, t_instru *instru, int line, char *param);
int			get_opcode(t_asm *asbly, char *str, int line);
int			is_register(char *param);
int			find_op_index(char *opcode);
int			get_nbr_of_params(char *opcode);
int			get_comma(char *str, int i);
int			get_last_param(t_asm *asmbly, char *str, int i, int line);
int			error_comma(t_asm *asmbly, char *str, int line, int i);
int			fill_params(t_asm *asmbly, t_instru **instru, char *str, int line);

/*
** conversion
*/
char		*reg_conver(t_asm *asmbly, t_param *param);
char		*dir_conver(t_asm *asmbly, t_param *param, t_instru *instru);
char		*ind_conver(t_asm *asmbly, t_param *param, t_instru *instru);
char		*fill_direct(t_asm *asmbly, int size, char **conv);
char		*reduce_conv(t_asm *asmbly, int size, char **conv);
char		*get_ocp(t_asm *asmbly, t_instru *instru);
void		replace_label(t_asm *asmbly);
void		convert_instruction(t_asm *asmbly);
void		write_label(t_instru *instru, char *conv);
int			reverse_label(t_asm *asmbly, t_instru *instru, char *label);
int			compare_label(char *label1, char *label2);
char		*convert_params(t_asm *asmbly, t_instru **instru);
void		get_label_value(t_asm *asmbly, t_instru *instru);

/*
** write file
*/
uint32_t	swap_endian(uint32_t val);
void		write_file(t_asm *asmbly, char *file);

void		free_prog(t_asm *asmbly);
void		quit_prog(t_asm *asmbly, int type);

/*
** debug
*/
void		print_instruction(t_asm *asmbly);
void		print_bytecode(char *str);

#endif
