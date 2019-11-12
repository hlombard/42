/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:55:18 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 14:55:19 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** The fork instruction creates a new process, that will inherit the
** different states of its father, except its PC.
** It takes only one argument which is the place where to start the
** new process and it doesn't modify the carry.
** There's no coding byte for the argument and its opcode is 0x0C.
*/

void	inst_fork(t_corewar *cor, t_plst *plst)
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
	elem->p.pc = pc_modulo(plst->p.og_pc
			+ ft_get_restricted_addr(arg.value[0], HALF));
	elem->next = cor->plst;
	cor->plst = elem;
	cor->nb_process++;
	cor->nb_process_max++;
	elem->n_plst = cor->nb_process_max;
	ft_verbosity_adv(cor, plst);
	if (DEBUG)
	{
		printf("##########  DEBUG FORK  ##########\n");
		ft_print_plst(cor->plst);
	}
}
