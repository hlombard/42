/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 13:40:46 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 13:40:54 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static inline void		ft_kill_nlp_2(t_corewar *cor, t_plst *plst)
{
	t_plst	*elem;

	while (plst->next != NULL)
	{
		if (plst->next->p.no_live >= cor->ctd)
		{
			if (cor->verbosity && (cor->v_lvl & VERBO4) && !cor->visu)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
					plst->next->n_plst, plst->next->p.no_live, cor->ctd);
			elem = plst->next;
			plst->next = plst->next->next;
			free(elem);
			cor->nb_process--;
		}
		else
			plst = plst->next;
		if (plst == NULL)
			return ;
	}
}

static inline void		ft_kill_no_live_process(t_corewar *cor)
{
	t_plst	*plst;

	plst = cor->plst;
	while (plst->p.no_live >= cor->ctd)
	{
		if (cor->verbosity && (cor->v_lvl & VERBO4) && !cor->visu)
			ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
					plst->n_plst, plst->p.no_live, cor->ctd);
		cor->plst = plst->next;
		free(plst);
		plst = cor->plst;
		cor->nb_process--;
		if (plst == NULL)
			return ;
	}
	ft_kill_nlp_2(cor, plst);
}

static inline void		reset_process_nb_live(t_corewar *cor)
{
	t_plst	*plst;
	int		i;

	plst = cor->plst;
	while (plst != NULL)
	{
		plst->p.live = 0;
		plst = plst->next;
	}
	i = -1;
	while (++i < cor->nb_players)
		cor->process[i].live_round = 0;
	cor->live_declared = 0;
}

void					update_cycles(t_corewar *cor)
{
	cor->check_cycle++;
	cor->cycle = 0;
	ft_kill_no_live_process(cor);
	if (cor->live_declared >= NBR_LIVE || cor->check_cycle == MAX_CHECKS)
	{
		cor->ctd -= CYCLE_DELTA;
		if (cor->visu)
			cor->round_end = cor->ctd;
		if (cor->verbosity && (cor->v_lvl & VERBO2) && !cor->visu)
			ft_printf("Cycle to die is now %d\n", cor->ctd);
		cor->check_cycle = 0;
	}
	reset_process_nb_live(cor);
}
