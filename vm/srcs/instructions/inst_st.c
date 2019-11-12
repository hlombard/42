/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_st.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:55:32 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 14:55:33 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** The st instruction is used to store the value from a registry to the memory
** It stores the value of the first argument toward the second argument and it
** doesn't modify the carry.
** There's a coding byte for the arguments and its opcode is 0x03.
*/

void		fill_value(t_corewar *cor, t_plst *plst, t_arg arg)
{
	if (arg.type[1] == REG_CODE)
		plst->p.reg[arg.value[1]] = arg.value[0];
	else
		print_value(cor, arg.value[0], plst->p.og_pc
			+ ft_get_restricted_addr(arg.value[1], FULL), plst);
}

void		inst_st(t_corewar *cor, t_plst *plst)
{
	t_arg	arg;

	ft_print_debug(plst, "ST", 0);
	arg = ft_arg_init(2, FULL, TRUE, NORMAL);
	ft_get_opcode(cor, plst, &arg);
	ft_get_args_size(&arg);
	if (arg.type[0] != REG_CODE
		|| ft_check_arg_type(arg, 1, IND_CODE, REG_CODE) == FAIL)
	{
		pc_modulo2(plst, ft_get_args_size_sum(arg));
		ft_verbosity_adv(cor, plst);
		return ;
	}
	ft_get_args(cor, plst, &arg);
	if (ft_check_reg_index(cor, plst, arg) == FAIL)
		return ;
	ft_verbosity_instru(cor, plst, arg);
	ft_get_reg_value(&arg, plst, FRST);
	fill_value(cor, plst, arg);
	ft_verbosity_adv(cor, plst);
	ft_print_debug(plst, "ST", 1);
}
