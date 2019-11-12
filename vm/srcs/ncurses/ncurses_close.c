/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_close.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:53:57 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 14:53:58 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	close_ncurses(t_corewar *cor)
{
	wclear(cor->render.main);
	delwin(cor->render.main);
	wclear(cor->render.menu);
	delwin(cor->render.menu);
	wclear(cor->render.commands);
	delwin(cor->render.commands);
	refresh();
	endwin();
	free_with_visu(cor);
}

void	free_with_visu(t_corewar *cor)
{
	t_plst	*p;
	t_plst	*tmp;

	p = cor->plst;
	while (p != NULL)
	{
		tmp = p;
		p = p->next;
		free(tmp);
	}
}

void	end_visu(t_corewar *cor)
{
	ncurses_show_winner(cor);
	wait_and_close(3);
	delwin(cor->render.main);
	delwin(cor->render.menu);
	delwin(cor->render.commands);
	endwin();
}

void	ncurses_show_winner(t_corewar *cor)
{
	int		i;

	i = -1;
	attron(COLOR_PAIR(15));
	while (++i < 50)
	{
		mvprintw(LINES / 3 - 2, (COLS / 2 - 105) + i, "*");
		mvprintw(LINES / 3 + 2, (COLS / 2 - 105) + i, "*");
	}
	i = -1;
	while (++i < 5)
	{
		mvprintw((LINES / 3 - 2) + i, (COLS / 2 - 105), "*");
		mvprintw((LINES / 3 - 2) + i, (COLS / 2 - 55), "*");
	}
	attroff(COLOR_PAIR(15));
	attron(COLOR_PAIR(13) | A_BOLD);
	mvprintw(LINES / 3, COLS / 2 - 100, "THE WINNER IS : \"%.15s\"",
			cor->player[ft_get_player_index(cor, cor->last_live_id)].name);
	attroff((COLOR_PAIR(13) | A_BOLD));
}

void	wait_and_close(int wait)
{
	refresh();
	sleep(wait);
	mvprintw(LINES / 3 + 3, COLS / 2 - 102,
			"Window will be automatically closed in 5s...");
	refresh();
	sleep(5);
}
