/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:54:09 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 14:54:15 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	draw_player_info(t_corewar *cor)
{
	int i;
	int y;

	y = 40;
	i = -1;
	while (++i < cor->nb_players)
	{
		wattron(cor->render.menu, COLOR_PAIR(i + 2) | A_BOLD);
		if (i == 3)
			wattron(cor->render.menu, COLOR_PAIR(14));
		mvwprintw(cor->render.menu, y, 3, "Player_%d : %.35s",
				i + 1, cor->process[i].name);
		mvwprintw(cor->render.menu, y + 2, 3, "Size : %d bytes  -",
				cor->process[i].size);
		mvwprintw(cor->render.menu, y + 2, 22, " Total lives : %d  -",
				cor->process[i].live);
		mvwprintw(cor->render.menu, y + 2, 43, "Lives / round : %d ",
				cor->process[i].live_round);
		wattroff(cor->render.menu, COLOR_PAIR(i + 2));
		if (i == 3)
			wattroff(cor->render.menu, COLOR_PAIR(14));
		wattroff(cor->render.menu, A_BOLD);
		y += 6;
	}
}

void	draw_infos(t_corewar *cor)
{
	draw_banner(cor);
	wattron(cor->render.menu, COLOR_PAIR(8) | A_BOLD);
	mvwprintw(cor->render.menu, 28, 3, "CYCLE_TO_DIE:  %d   ", cor->ctd);
	mvwprintw(cor->render.menu, 30, 30, "Current round ends in: %d  Cycles ",
			cor->round_end);
	mvwprintw(cor->render.menu, 29, 3, "CYCLE_DELTA:   %d   ", CYCLE_DELTA);
	mvwprintw(cor->render.menu, 30, 3, "MAX_CHECKS:    %d   ", MAX_CHECKS);
	mvwprintw(cor->render.menu, 31, 3, "NBR_LIVE:      %d   ", NBR_LIVE);
	wattroff(cor->render.menu, COLOR_PAIR(8) | A_BOLD);
	wattron(cor->render.menu, COLOR_PAIR(2) | A_BOLD);
	mvwprintw(cor->render.menu, 33, 3, "CYCLE:           %d   ",
			cor->total_cycle);
	mvwprintw(cor->render.menu, 34, 3, "PROCESSES:       %d   ",
			cor->nb_process);
	mvwprintw(cor->render.menu, 33, 30, "Total lives / round:  %d   ",
			cor->live_declared);
	mvwprintw(cor->render.menu, 34, 30, "Speed (usleep/cycle): %d   ",
			cor->sleep);
	wattroff(cor->render.menu, COLOR_PAIR(2) | A_BOLD);
}

void	draw_banner(t_corewar *cor)
{
	wattron(cor->render.menu, A_BOLD);
	wattron(cor->render.menu, COLOR_PAIR(2));
	mvwprintw(cor->render.menu, 19, 12, STR1);
	wattroff(cor->render.menu, COLOR_PAIR(2));
	wattron(cor->render.menu, COLOR_PAIR(3));
	mvwprintw(cor->render.menu, 20, 12, STR2);
	wattroff(cor->render.menu, COLOR_PAIR(3));
	wattron(cor->render.menu, COLOR_PAIR(4));
	mvwprintw(cor->render.menu, 21, 12, STR3);
	wattroff(cor->render.menu, COLOR_PAIR(4));
	wattron(cor->render.menu, COLOR_PAIR(5));
	mvwprintw(cor->render.menu, 22, 12, STR4);
	wattroff(cor->render.menu, COLOR_PAIR(5));
	wattron(cor->render.menu, COLOR_PAIR(13));
	mvwprintw(cor->render.menu, 23, 12, STR5);
	wattroff(cor->render.menu, COLOR_PAIR(13));
	wattron(cor->render.menu, COLOR_PAIR(2));
	mvwprintw(cor->render.menu, 24, 12, STR6);
	wattroff(cor->render.menu, COLOR_PAIR(2));
	wattroff(cor->render.menu, A_BOLD);
}

void	draw_command(t_corewar *cor)
{
	wattron(cor->render.commands, COLOR_PAIR(13));
	wattron(cor->render.commands, A_BOLD);
	mvwprintw(cor->render.commands, 2, 15, "-[ COMMANDS MENU ]-");
	mvwprintw(cor->render.commands, 5, 3, "SPACE :  PAUSE / UNPAUSE");
	wattroff(cor->render.commands, COLOR_PAIR(13));
	wattron(cor->render.commands, COLOR_PAIR(8));
	mvwprintw(cor->render.commands, 7, 3, "'+' :  Speed UP");
	mvwprintw(cor->render.commands, 9, 3, "'-' :  Slow DOWN");
	wattroff(cor->render.commands, COLOR_PAIR(8));
	wattron(cor->render.commands, COLOR_PAIR(4));
	mvwprintw(cor->render.commands, 11, 3, "Q :  QUIT");
	wattroff(cor->render.commands, COLOR_PAIR(4));
	wattroff(cor->render.commands, A_BOLD);
}
