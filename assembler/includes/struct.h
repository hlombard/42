/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 19:46:31 by ratin             #+#    #+#             */
/*   Updated: 2019/09/04 12:13:36 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "op.h"

struct					s_type
{
	int					param1;
	int					param2;
	int					param3;
};

typedef struct			s_op
{
	char				*name;
	int					nbr_of_param;
	struct s_type		type_of_param;
	int					opcode;
	int					nbr_of_cycle;
	char				*description;
	unsigned int		coding_opcode;
	unsigned int		direct_size;
}						t_op;

typedef struct			s_asm
{
	char				*name;
	char				comment[COMMENT_LENGTH + 1];
	int					size;
	int					got_name;
	int					got_comment;
	int					in_comment;
	int					idx_comment;
	struct s_op			op_tab[17];
	struct s_instru		*instru;
}						t_asm;

typedef struct			s_param
{
	int					type;
	char				*param;
	int					line;
	struct s_param		*next;
}						t_param;

typedef struct			s_instru
{
	char				*conv_par;
	char				*label;
	char				*opcode;
	int					nbr_opcode;
	int					added_label;
	int					labelsrc;
	int					byte_size;
	int					line;
	int					nbr_of_params;
	struct s_param		*param;
	struct s_instru		*next;
}						t_instru;

#endif
