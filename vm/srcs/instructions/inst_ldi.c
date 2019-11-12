/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_ldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:55:22 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 14:55:23 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** The ldi instruction add the first two arguments together, treating that
** as an address from where the value at this address, will be loaded in
** the third argument. It doesn't modify the carry.
** There's a coding byte for the arguments and its opcode is 0x0A.
*/

static inline int	ft_fill_value(t_corewar *cor, t_plst *plst, t_arg *arg)
{
	unsigned int	j;
	int				result;

	result = 0;
	j = 0;
	while (j < REG_SIZE)
	{
		result = (result << 8);
		result += cor->arena[pc_modulo(plst->p.og_pc
				+ ft_get_restricted_addr(arg->value[0]
				+ arg->value[1], FULL) + j)];
		j++;
	}
	return (result);
}

void				inst_ldi(t_corewar *cor, t_plst *plst)
{
	t_arg	arg;

	ft_print_debug(plst, "LDI", 0);
	arg = ft_arg_init(3, HALF, TRUE, INDIRECT);
	ft_get_opcode(cor, plst, &arg);
	ft_get_args_size(&arg);
	if (arg.type[0] == 0 || !ft_check_arg_type(arg, 1, REG_CODE, DIR_CODE)
			|| arg.type[2] != REG_CODE)
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
	plst->p.reg[arg.value[2]] = ft_fill_value(cor, plst, &arg);
	ft_verbosity_adv(cor, plst);
	ft_print_debug(plst, "LDI", 1);
}
