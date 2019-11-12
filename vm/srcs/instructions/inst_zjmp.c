/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_zjmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:55:42 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 14:55:43 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** The zjmp instruction jumps to a given part of the memory.
** It takes only one argument which is the part of the memory that you
** want to access and it jumps there only if the carry is set to 1, but
** does not modify the carry.
** There's no coding byte for the argument and its opcode is 0x09.
*/

void	inst_zjmp(t_corewar *cor, t_plst *plst)
{
	t_arg	arg;

	ft_print_debug(plst, "ZJMP", 0);
	arg = ft_arg_init(1, HALF, TRUE, SPECIAL);
	arg.type[0] = DIR_CODE;
	arg.size[0] = 2;
	ft_get_args(cor, plst, &arg);
	ft_verbosity_instru(cor, plst, arg);
	arg.value[0] = ft_get_restricted_addr(arg.value[0], HALF);
	if (plst->p.carry == 1)
		plst->p.pc = pc_modulo(plst->p.og_pc
				+ arg.value[0]);
	else
		ft_verbosity_adv(cor, plst);
	ft_print_debug(plst, "ZJMP", 1);
}
