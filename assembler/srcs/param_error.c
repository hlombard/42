/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 23:27:45 by ratin             #+#    #+#             */
/*   Updated: 2019/09/05 16:51:41 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				nbr_prm(t_asm *asmbly, t_instru *instru, char *str, int line)
{
	t_param		*last;
	int			i;

	last = instru->param;
	i = 0;
	while (last)
	{
		last = last->next;
		i++;
	}
	if (i != instru->nbr_of_params)
		print_erro_param(asmbly, str, line, 2);
	return (0);
}

int				multi_param_checker(int type, int checker)
{
	if ((type | T_REG) == checker)
		return (0);
	if ((type | T_DIR) == checker)
		return (0);
	if ((type | T_IND) == checker)
		return (0);
	if ((type | T_DIR | T_IND) == checker)
		return (0);
	if ((type | T_REG | T_IND) == checker)
		return (0);
	if ((type | T_REG | T_DIR) == checker)
		return (0);
	return (-1);
}

int				check_para(int para_index, int i, t_param *last)
{
	extern t_op	g_op_tab[17];
	int			checker;

	if (para_index == 1)
		checker = g_op_tab[i].type_of_param.param1;
	if (para_index == 2)
		checker = g_op_tab[i].type_of_param.param2;
	if (para_index == 3)
		checker = g_op_tab[i].type_of_param.param3;
	if (checker == 1 || checker == 2 || checker == 4)
	{
		if (last->type != checker)
			return (-1);
	}
	else
		return (multi_param_checker(last->type, checker));
	return (0);
}

int				check_type(t_asm *asmbly, t_instru *instru, int line, char *str)
{
	t_param		*last;
	int			i;
	int			para_index;

	i = find_op_index(instru->opcode);
	para_index = 1;
	last = instru->param;
	while (last)
	{
		if (check_para(para_index, i, last) == -1)
		{
			free(str);
			p_error(asmbly, last, line, instru);
		}
		para_index++;
		last = last->next;
	}
	return (0);
}

void			check_params_error(t_asm *asmbly, char *str, int line)
{
	t_instru	*current;

	if (!(current = find_instru(asmbly, line)))
		current = get_last_instru(asmbly);
	nbr_prm(asmbly, current, str, line);
	check_type(asmbly, current, line, str);
}
