/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:55:24 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 14:55:25 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** The lfork instruction works the same as the fork instruction, the only
** difference is that it does not use '% IND_MOD'.
** There's no coding byte for the arguments and its opcode is 0x0F.
*/

void	inst_lfork(t_corewar *cor, t_plst *plst)
{
	t_arg	arg;
	t_plst	*elem;

	arg = ft_arg_init(1, HALF, TRUE, SPECIAL);
	arg.type[0] = DIR_CODE;
	arg.size[0] = 2;
	ft_get_args(cor, plst, &arg);
	if (!(elem = malloc(sizeof(t_plst))))
		corewar_quit("Fail malloc");
	ft_verbosity_instru(cor, plst, arg);
	plst->p.opcode = 0;
	ft_memcpy(elem, plst, sizeof(t_plst));
	elem->p.pc = pc_modulo(plst->p.og_pc + arg.value[0]);
	elem->next = cor->plst;
	cor->plst = elem;
	cor->nb_process++;
	cor->nb_process_max++;
	elem->n_plst = cor->nb_process_max;
	ft_verbosity_adv(cor, plst);
	if (DEBUG)
	{
		printf("##########  DEBUG LFORK  ##########\n");
		printf("Cycle is %d\n", cor->total_cycle);
		ft_print_plst(cor->plst);
	}
}
