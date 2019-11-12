/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_sti.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:55:36 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 14:55:37 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** The sti instruction add the last two arguments together, treating that
** as an address from where the value of the first argument will be stored at
** and it doesn't modify the carry.
** There's a coding byte for the arguments and its opcode is 0x0B.
*/

void	print_value(t_corewar *cor, int value, int addr, t_plst *plst)
{
	char	c;
	int		i;

	i = 0;
	addr = pc_modulo(addr);
	while (i < 4)
	{
		c = (value >> (8 * (3 - i))) & 0xFF;
		cor->arena[addr] = c;
		cor->render.bold[addr] = 50;
		cor->render.mem_owner[addr] = re_adjust_id(plst->p.id, &plst->p) + 1;
		addr = pc_modulo(addr + 1);
		i++;
	}
}

void	inst_sti(t_corewar *cor, t_plst *plst)
{
	t_arg	arg;

	ft_print_debug(plst, "STI", 0);
	arg = ft_arg_init(3, HALF, TRUE, INDIRECT);
	ft_get_opcode(cor, plst, &arg);
	ft_get_args_size(&arg);
	if (arg.type[0] != REG_CODE || arg.type[1] == 0
		|| ft_check_arg_type(arg, 2, DIR_CODE, REG_CODE) == FAIL)
	{
		pc_modulo2(plst, ft_get_args_size_sum(arg));
		ft_verbosity_adv(cor, plst);
		return ;
	}
	ft_get_args(cor, plst, &arg);
	if (ft_check_reg_index(cor, plst, arg) == FAIL)
		return ;
	ft_get_reg_value(&arg, plst, SCND | THRD);
	ft_verbosity_instru(cor, plst, arg);
	ft_get_reg_value(&arg, plst, FRST);
	print_value(cor, arg.value[0],
			plst->p.og_pc
			+ ft_get_restricted_addr(arg.value[1] + arg.value[2], FULL), plst);
	ft_verbosity_adv(cor, plst);
	ft_print_debug(plst, "STI", 1);
}
