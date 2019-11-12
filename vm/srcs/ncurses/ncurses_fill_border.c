/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_fill_border.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:54:04 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 14:54:06 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fill_border_main(t_corewar *cor)
{
	int i;

	i = -1;
	wattron(cor->render.main, COLOR_PAIR(6));
	while (i++ < BOX_COL_1)
	{
		mvwaddch(cor->render.main, BOX_LINES_1 - 1, i, '*');
		mvwaddch(cor->render.main, 0, i, '*');
	}
	i = -1;
	while (++i < BOX_LINES_1)
	{
		mvwaddch(cor->render.main, i, BOX_COL_1 - 1, '*');
		mvwaddch(cor->render.main, i, 0, '*');
	}
	wattroff(cor->render.main, COLOR_PAIR(6));
}

void	fill_border_menu(t_corewar *cor)
{
	int i;

	i = -1;
	wattron(cor->render.menu, COLOR_PAIR(6));
	while (++i < BOX_COL_2)
	{
		mvwaddch(cor->render.menu, BOX_LINES_1 - 1, i, '*');
		mvwaddch(cor->render.menu, 0, i, '*');
	}
	i = -1;
	while (i++ < BOX_LINES_1)
	{
		mvwaddch(cor->render.menu, i, BOX_COL_2 - 1, '*');
	}
	wattroff(cor->render.menu, COLOR_PAIR(6));
}

void	fill_border_cmd(t_corewar *cor)
{
	int i;

	i = -1;
	wattron(cor->render.commands, COLOR_PAIR(6));
	while (++i < 50)
	{
		mvwaddch(cor->render.commands, 0, i, '*');
		mvwaddch(cor->render.commands, 14, i, '*');
	}
	i = -1;
	while (++i < 15)
		mvwaddch(cor->render.commands, i, 49, '*');
	wattroff(cor->render.commands, COLOR_PAIR(6));
}
