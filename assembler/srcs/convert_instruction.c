/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_instruction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 20:01:04 by ratin             #+#    #+#             */
/*   Updated: 2019/09/05 16:41:28 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static char		*convert_opcode(t_asm *asmbly, t_instru *instru)
{
	extern t_op	g_op_tab[17];
	char		*conv;
	char		*c_opcode;
	int			op_index;
	int			size;

	size = 2;
	c_opcode = NULL;
	op_index = find_op_index(instru->opcode);
	if (!(c_opcode = ft_itoa(g_op_tab[op_index].opcode)))
		quit_prog(asmbly, 0);
	if (!(conv = ft_ul_convert_base(c_opcode, "0123456789abcdef")))
		quit_prog(asmbly, 0);
	free(c_opcode);
	size -= ft_strlen(conv);
	if (size > 0)
		conv = fill_direct(asmbly, size, &conv);
	else if (size < 0)
		conv = reduce_conv(asmbly, size, &conv);
	return (conv);
}

static int		add_byte_size(t_instru *instru)
{
	int			result;
	int			i;

	i = 0;
	result = 0;
	while (instru->conv_par[i])
	{
		if (i % 2 == 0 && instru->conv_par[i] != ';')
			result++;
		i++;
	}
	return (result);
}

void			get_elements(t_asm *asmbly, t_instru **instru)
{
	extern t_op	g_op_tab[17];
	int			op_index;

	op_index = find_op_index((*instru)->opcode);
	(*instru)->conv_par = convert_opcode(asmbly, (*instru));
	if (g_op_tab[op_index].coding_opcode == 1)
	{
		(*instru)->conv_par = ft_strjoin_free((*instru)->conv_par
			, get_ocp(asmbly, (*instru)), 3);
	}
	(*instru)->conv_par = ft_strjoin_free((*instru)->conv_par
		, convert_params(asmbly, &(*instru)), 3);
	(*instru)->byte_size = add_byte_size((*instru));
}

void			convert_instruction(t_asm *asmbly)
{
	t_instru	*instru;
	int			i;

	i = 0;
	instru = NULL;
	instru = asmbly->instru;
	while (instru)
	{
		if (instru->opcode == NULL)
		{
			instru = instru->next;
			continue ;
		}
		get_elements(asmbly, &instru);
		instru = instru->next;
	}
	while (i < 3)
	{
		replace_label(asmbly);
		i++;
	}
}
