/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:55:37 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 14:55:38 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** The sub instruction is used to subtract two values.
** It takes three arguments, subtract the first two arguments together and
** put the result in the third argument and it sets the carry to 1 if the
** result is equal to 0, otherwise it sets the carry to 0.
** There's a coding byte for the arguments and its opcode is 0x05.
*/

void	inst_sub(t_corewar *cor, t_plst *plst)
{
	t_arg	arg;

	ft_print_debug(plst, "SUB", 0);
	arg = ft_arg_init(3, FULL, TRUE, NORMAL);
	ft_get_opcode(cor, plst, &arg);
	ft_get_args_size(&arg);
	if (arg.type[0] != REG_CODE || arg.type[1] != REG_CODE
			|| arg.type[2] != REG_CODE)
	{
		pc_modulo2(plst, ft_get_args_size_sum(arg));
		ft_verbosity_adv(cor, plst);
		return ;
	}
	ft_get_args(cor, plst, &arg);
	if (ft_check_reg_index(cor, plst, arg) == FAIL)
		return ;
	ft_verbosity_instru(cor, plst, arg);
	ft_get_reg_value(&arg, plst, FRST | SCND);
	plst->p.reg[arg.value[2]] = arg.value[0] - arg.value[1];
	plst->p.carry = (plst->p.reg[arg.value[2]] == 0);
	ft_verbosity_adv(cor, plst);
	ft_print_debug(plst, "SUB", 1);
}
