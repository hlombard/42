/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:55:16 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 14:55:17 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** The and instruction apply an & (bit-to-bit AND).
** It apply an & over the first two arguments and store the result in the
** third argument and sets the carry to 1 if the result is equal to 0,
** otherwise it sets it to 0.
** There's a coding byte for the arguments and its opcode is 0x06.
*/

void	inst_and(t_corewar *cor, t_plst *plst)
{
	t_arg	arg;

	ft_print_debug(plst, "AND", 0);
	arg = ft_arg_init(3, FULL, TRUE, NORMAL);
	ft_get_opcode(cor, plst, &arg);
	ft_get_args_size(&arg);
	if (arg.type[0] == 0 || arg.type[1] == 0 || arg.type[2] != REG_CODE)
	{
		pc_modulo2(plst, ft_get_args_size_sum(arg));
		ft_verbosity_adv(cor, plst);
		return ;
	}
	ft_get_args(cor, plst, &arg);
	if (ft_check_reg_index(cor, plst, arg) == FAIL)
		return ;
	ft_get_reg_value(&arg, plst, FRST | SCND);
	ft_verbosity_instru(cor, plst, arg);
	plst->p.reg[arg.value[2]] = arg.value[0] & arg.value[1];
	plst->p.carry = arg.value[0] & arg.value[1] ? 0 : 1;
	ft_verbosity_adv(cor, plst);
	ft_print_debug(plst, "AND", 1);
}
