/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 15:15:11 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 15:15:12 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ft_print_debug(t_plst *plst, char *op_name, int end)
{
	if (DEBUG)
	{
		if (end == 0)
			ft_printf("##################  %s  ##################\n", op_name);
		ft_printf("%s\n", end ? "\nAFTER\n" : "BEFORE\n");
		ft_print_process(plst->p);
		if (end == 1)
			ft_printf("##################  END  ##################\n");
	}
}

void	ft_print_args(t_arg arg)
{
	int	i;

	ft_printf("Arg number: %d\n", arg.nb_arg);
	i = 0;
	while (i < arg.nb_arg)
	{
		ft_printf("Arg %d: size: [%u], value: [%d]\n",
				i, arg.size[i], arg.value[i]);
		i++;
	}
}

void	ft_print_process(t_process p)
{
	int		i;

	i = 1;
	ft_printf("Name: %-*s\n", PROG_NAME_LENGTH, p.name);
	ft_printf("ID: %d\n", p.id);
	ft_printf("PC: %u\n", p.pc);
	ft_printf("OG_PC: %u\n", p.og_pc);
	ft_printf("Carry: %u\n", p.carry);
	ft_printf("live: %u\n", p.live);
	ft_printf("No_live: %d\n", p.no_live);
	ft_printf("Wait: %d\n", p.wait);
	ft_printf("Op code: %d\n", p.opcode);
	ft_printf("REG\n");
	while (i <= REG_NUMBER)
	{
		ft_printf("[%d]: %d\n", i, p.reg[i]);
		i++;
	}
}

void	ft_print_plst(t_plst *plst)
{
	while (plst != NULL)
	{
		ft_print_process(plst->p);
		plst = plst->next;
	}
}
