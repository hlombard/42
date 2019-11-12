/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 13:40:57 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 13:41:00 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void (*g_func[17])(t_corewar *cor, t_plst *plst) =
{
	inst_live,
	inst_ld,
	inst_st,
	inst_add,
	inst_sub,
	inst_and,
	inst_or,
	inst_xor,
	inst_zjmp,
	inst_ldi,
	inst_sti,
	inst_fork,
	inst_lld,
	inst_lldi,
	inst_lfork,
	inst_aff
};

static inline void	ft_get_instru(t_corewar *cor, t_plst *plst)
{
	if (cor->arena[plst->p.pc] <= 17 && cor->arena[plst->p.pc] >= 1)
	{
		plst->p.opcode = cor->arena[plst->p.pc];
		plst->p.og_pc = plst->p.pc;
		plst->p.wait = g_op_tab[plst->p.opcode - 1].nbr_of_cycle - 1;
		pc_modulo2(plst, 1);
	}
	else
	{
		plst->p.opcode = 0;
		pc_modulo2(plst, 1);
		plst->p.og_pc = plst->p.pc;
	}
}

static inline void	execute_code(t_corewar *cor, t_plst *plst)
{
	g_func[plst->p.opcode - 1](cor, plst);
	plst->p.opcode = 0;
}

static inline void	exec_process(t_corewar *cor)
{
	t_plst	*plst;

	plst = cor->plst;
	while (plst != NULL)
	{
		plst->p.no_live++;
		if (plst->p.opcode == 0)
			ft_get_instru(cor, plst);
		else
		{
			plst->p.wait--;
			if (plst->p.wait == 0)
				execute_code(cor, plst);
		}
		plst = plst->next;
	}
}

void				play(t_corewar *cor)
{
	if (cor->visu)
		draw_window(cor);
	cor->last_live_id = cor->plst->p.id;
	while (cor->plst != NULL)
	{
		if (cor->visu)
			update_window(cor);
		cor->cycle++;
		cor->total_cycle++;
		if (cor->verbosity && (cor->v_lvl & VERBO2) && !cor->visu)
			ft_printf("It is now cycle %d\n", cor->total_cycle);
		exec_process(cor);
		if (cor->total_cycle == cor->n_dump)
		{
			print_arena_state(cor);
			cor->hide_winner = 1;
			return ;
		}
		if (cor->cycle >= cor->ctd)
			update_cycles(cor);
	}
}

void				introducing_contestants(t_corewar *cor)
{
	int		i;

	i = -1;
	if (!cor->visu)
	{
		ft_printf("Introducing contestants...\n");
		while (++i < cor->nb_players)
		{
			ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				i + 1, cor->process[i].size, cor->process[i].name,
					cor->process[i].comment);
		}
	}
}
