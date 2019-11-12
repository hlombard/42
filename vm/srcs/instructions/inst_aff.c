/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_aff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:55:14 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 14:55:15 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** The aff instruction takes a registry as its only argument, writes
** the value of the registry to the standard output and it doesn't
** modify the carry.
** There's a coding byte for the argument and its opcode is 0x10.
*/

void	inst_aff(t_corewar *cor, t_plst *plst)
{
	t_arg	arg;

	ft_print_debug(plst, "AFF", 0);
	arg = ft_arg_init(1, FULL, TRUE, SPECIAL);
	ft_get_opcode(cor, plst, &arg);
	ft_get_args_size(&arg);
	if (arg.type[0] != REG_CODE)
	{
		pc_modulo2(plst, ft_get_args_size_sum(arg));
		ft_verbosity_adv(cor, plst);
		return ;
	}
	ft_get_args(cor, plst, &arg);
	if (ft_check_reg_index(cor, plst, arg) == FAIL)
		return ;
	ft_verbosity_instru(cor, plst, arg);
	if (cor->aff && !cor->visu)
		ft_printf("Aff: %c\n", plst->p.reg[arg.value[0]] % 256);
	ft_verbosity_adv(cor, plst);
	ft_print_debug(plst, "AFF", 1);
}
