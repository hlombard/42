/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 13:37:46 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 13:47:43 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

t_op				g_op_tab[17] =
{
	{"live", 1, {T_DIR, 0, 0}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG, 0}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG, 0}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR, 0, 0}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR, 0, 0}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG, 0}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR, 0, 0}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG, 0, 0}, 16, 2, "aff", 1, 0},
	{0, 0, {0, 0, 0}, 0, 0, 0, 0, 0}
};

static inline void	create_arena(t_corewar *cor)
{
	int		i;

	i = -1;
	if (cor->visu)
		init_ncurse(cor);
	ft_bzero(cor->arena, MEM_SIZE);
	while (++i < cor->nb_players)
	{
		ft_memcpy((void*)&cor->arena + ((MEM_SIZE / cor->nb_players) * i),
				cor->process[i].code, cor->process[i].size);
		cor->process[i].pc = (MEM_SIZE / cor->nb_players) * i;
		cor->process[i].og_pc = cor->process[i].pc;
		if (cor->visu)
		{
			ft_memset(cor->render.mem_owner + ((MEM_SIZE / cor->nb_players)
						* i), (char)(i + 2), cor->process[i].size);
		}
	}
}

static inline void	init_datas(t_corewar *cor)
{
	ft_bzero(cor, sizeof(t_corewar));
	cor->ctd = CYCLE_TO_DIE;
	cor->n_dump = -1;
}

int					main(int ac, char **av)
{
	t_corewar	cor;

	if (ac < 2)
	{
		corewar_usage();
		return (0);
	}
	init_datas(&cor);
	parse_arguments(ac, av, &cor);
	parse_arguments_2(&cor);
	create_arena(&cor);
	introducing_contestants(&cor);
	if (cor.n_dump == 0)
	{
		print_arena_state(&cor);
		return (1);
	}
	if (!(cor.plst = ft_plst_init(&cor)))
		corewar_quit("Malloc error");
	ft_player_init(&cor);
	play(&cor);
	corewar_end(&cor);
	return (1);
}

void				corewar_end(t_corewar *cor)
{
	int		winner;

	if (cor->visu)
		end_visu(cor);
	winner = cor->last_live_id;
	if (!cor->hide_winner && !cor->visu)
	{
		if (winner == 0)
			ft_printf("No contestant managed to make a succesful live. DRAW\n");
		else
			ft_printf("Contestant %d, \"%s\", has won !\n", winner * -1,
					cor->player[ft_get_player_index(cor, winner)].name);
	}
}
