/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pc_modulo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:18:52 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 14:19:02 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	pc_modulo2(t_plst *plst, int i)
{
	plst->p.pc = pc_modulo(plst->p.pc + i);
}

int		pc_modulo(int pc)
{
	if (pc < 0)
	{
		while (pc < 0)
			pc += MEM_SIZE;
	}
	else if (pc >= MEM_SIZE)
	{
		while (pc >= MEM_SIZE)
			pc -= MEM_SIZE;
	}
	return (pc);
}
