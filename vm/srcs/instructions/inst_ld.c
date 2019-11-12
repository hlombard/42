/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_ld.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:55:21 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 14:55:22 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** The ld instruction is used to load values from memory to a registry.
** It load the value from the first argument to the second argument and
** sets the carry to 1 if the value of the first argument is 0, else to 0.
** There's a coding byte for the arguments and its opcode is 0x02.
*/

void	inst_ld(t_corewar *cor, t_plst *plst)
{
	t_arg	arg;

	ft_print_debug(plst, "LD", 0);
	arg = ft_arg_init(2, FULL, TRUE, NORMAL);
	ft_get_opcode(cor, plst, &arg);
	ft_get_args_size(&arg);
	if (ft_check_arg_type(arg, 0, IND_CODE, DIR_CODE) == FAIL
			|| arg.type[1] != REG_CODE)
	{
		pc_modulo2(plst, ft_get_args_size_sum(arg));
		ft_verbosity_adv(cor, plst);
		return ;
	}
	ft_get_args(cor, plst, &arg);
	if (ft_check_reg_index(cor, plst, arg) == FAIL)
		return ;
	ft_verbosity_instru(cor, plst, arg);
	plst->p.reg[arg.value[1]] = arg.value[0];
	plst->p.carry = !(arg.value[0]);
	ft_verbosity_adv(cor, plst);
	ft_print_debug(plst, "LD", 1);
}
