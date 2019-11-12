/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_button.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:53:53 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 14:53:55 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	draw_play(t_corewar *cor)
{
	werase(cor->render.menu);
	fill_border_menu(cor);
	draw_menu(cor);
	wattron(cor->render.menu, A_BOLD | COLOR_PAIR(2));
	draw_play_1(cor, 49, 24, 6);
	draw_play_2(cor, 49, 24, 10);
	wattroff(cor->render.menu, A_BOLD | COLOR_PAIR(2));
	wattron(cor->render.menu, COLOR_PAIR(3) | A_BOLD);
	mvwprintw(cor->render.menu, 1, 28, "***  LIVE  ***");
	wattroff(cor->render.menu, COLOR_PAIR(3) | A_BOLD);
	wrefresh(cor->render.menu);
}

void	draw_play_1(t_corewar *cor, int x, int x1, int y1)
{
	int y;

	y = 4;
	while (y++ < 16)
		mvwprintw(cor->render.menu, y, 25, "#");
	y = 10;
	while (x1 >= 0 && y1 >= 0)
	{
		mvwprintw(cor->render.menu, y - y1, x - x1, "#");
		x1 -= 4;
		y1--;
	}
}

void	draw_play_2(t_corewar *cor, int x, int x1, int y)
{
	int y1;

	y1 = 6;
	while (x1 >= 0 && y1 >= 0)
	{
		mvwprintw(cor->render.menu, y + y1, x - x1, "#");
		x1 -= 4;
		y1--;
	}
}

void	draw_pause(t_corewar *cor)
{
	int y;

	werase(cor->render.menu);
	fill_border_menu(cor);
	draw_menu(cor);
	wattron(cor->render.menu, COLOR_PAIR(4) | A_BOLD);
	y = 3;
	while (y++ < 14)
		mvwprintw(cor->render.menu, y, 23, "#");
	y = 3;
	while (y++ < 14)
		mvwprintw(cor->render.menu, y, 24, "#");
	y = 3;
	while (y++ < 14)
		mvwprintw(cor->render.menu, y, 45, "#");
	y = 3;
	while (y++ < 14)
		mvwprintw(cor->render.menu, y, 46, "#");
	wattroff(cor->render.menu, COLOR_PAIR(4) | A_BOLD);
	wattron(cor->render.menu, COLOR_PAIR(3) | A_BOLD);
	mvwprintw(cor->render.menu, 1, 27, "***  PAUSED  ***");
	wattroff(cor->render.menu, COLOR_PAIR(3) | A_BOLD);
	wrefresh(cor->render.menu);
}
