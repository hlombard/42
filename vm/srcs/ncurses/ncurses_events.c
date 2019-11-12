/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:54:02 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 14:54:03 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	ncurse_events(t_corewar *cor)
{
	int keycode;

	keycode = getch();
	if (keycode == SPACE_BAR)
	{
		if (cor->pause == 1)
		{
			cor->pause = 0;
			draw_play(cor);
		}
		else
		{
			cor->pause = 1;
			pause_game(cor);
		}
	}
	if (keycode == '+' && cor->sleep > 0)
		cor->sleep -= 500;
	if (keycode == '-' && cor->sleep < 100000)
		cor->sleep += 500;
	if (keycode == QUIT)
	{
		close_ncurses(cor);
		corewar_quit("Game closed, \"Q\" has been pressed.");
	}
}

void	pause_game(t_corewar *cor)
{
	int keycode;

	draw_pause(cor);
	while (42)
	{
		keycode = getch();
		if (keycode == SPACE_BAR)
		{
			cor->pause = 0;
			draw_play(cor);
			return ;
		}
		manage_pause(cor, keycode);
	}
}

void	manage_pause(t_corewar *cor, int keycode)
{
	if (keycode == QUIT)
	{
		close_ncurses(cor);
		corewar_quit("Game closed, \"Q\" has been pressed.");
	}
	else if (keycode == '+' && cor->sleep > 0)
	{
		cor->sleep -= 500;
		draw_menu(cor);
	}
	else if (keycode == '-' && cor->sleep < 100000)
	{
		cor->sleep += 500;
		draw_menu(cor);
	}
}
