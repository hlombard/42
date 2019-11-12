/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_lld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:55:28 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 14:55:29 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** The lld instruction works the same as the ld instruction, the only
** difference is that it does not use '% IND_MOD'.
** There's a coding byte for the arguments and its opcode is 0x0D.
*/

void	inst_lld(t_corewar *cor, t_plst *plst)
{
	t_arg	arg;

	ft_print_debug(plst, "LLD", 0);
	arg = ft_arg_init(2, FULL, FALSE, NORMAL);
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
	arg.value[0] = arg.type[0] == DIR_CODE ? arg.value[0] : arg.value[0] >> 16;
	ft_verbosity_instru(cor, plst, arg);
	plst->p.reg[arg.value[1]] = arg.value[0];
	plst->p.carry = !(plst->p.reg[arg.value[1]]);
	ft_verbosity_adv(cor, plst);
	ft_print_debug(plst, "LLD", 1);
}
