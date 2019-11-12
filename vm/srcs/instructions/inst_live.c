/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_live.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:55:26 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 14:55:27 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** The live instruction allows a process to stay alive.
** It takes only one argument, which is the player's number, to record
** if the player is indeed alive and it doesn't modify the carry.
** There's no coding byte for the argument and its opcode is 0x01.
*/

int					ft_get_player_index(t_corewar *cor, int i)
{
	int		j;

	j = 0;
	while (j < cor->nb_players)
	{
		if (cor->player[j].id == i)
			return (j);
		j++;
	}
	return (-1);
}

void				inst_live(t_corewar *cor, t_plst *plst)
{
	t_arg	arg;
	int		index;

	ft_print_debug(plst, "LIVE", 0);
	arg = ft_arg_init(1, FULL, FALSE, SPECIAL);
	arg.type[0] = DIR_CODE;
	arg.size[0] = 4;
	ft_get_args(cor, plst, &arg);
	index = ft_get_player_index(cor, arg.value[0]);
	ft_verbosity_instru(cor, plst, arg);
	(plst->p.live)++;
	if (index != -1)
	{
		cor->process[cor->nb_players - 1 - index].live++;
		cor->process[cor->nb_players - 1 - index].live_round++;
		cor->last_live_id = arg.value[0];
	}
	cor->live_declared++;
	plst->p.no_live = 0;
	ft_verbosity_adv(cor, plst);
	ft_print_debug(plst, "LIVE", 1);
}
