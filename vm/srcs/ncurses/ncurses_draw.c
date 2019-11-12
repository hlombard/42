/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:53:59 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 14:54:01 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	draw_arena(t_corewar *cor)
{
	int				x;
	int				y;
	int				i;
	unsigned char	color;

	i = 0;
	y = -1;
	while (++y < 64)
	{
		x = -1;
		while (++x < 64)
		{
			color = cor->render.mem_owner[i];
			set_attributes(cor, color, i);
			cor->stealth ? mvwprintw(cor->render.main, y + 2, x * 3 + 3, "ff")
				: mvwprintw(cor->render.main, y + 2, x * 3 + 3, "%.2x",
						cor->arena[i]);
			unset_attributes(cor, color, i);
			mvwprintw(cor->render.main, y + 2, x * 3 + 5, " ");
			i++;
		}
	}
	highlight_process_pc(cor);
	wrefresh(cor->render.main);
}

void	draw_window(t_corewar *cor)
{
	cor->round_end = cor->ctd;
	draw_arena(cor);
	fill_border_main(cor);
	fill_border_cmd(cor);
	draw_command(cor);
	pause_game(cor);
	nodelay(stdscr, 1);
}

void	draw_menu(t_corewar *cor)
{
	draw_infos(cor);
	draw_player_info(cor);
	wrefresh(cor->render.menu);
}

void	update_window(t_corewar *cor)
{
	draw_arena(cor);
	draw_menu(cor);
	ncurse_events(cor);
	cor->round_end--;
	usleep(cor->sleep);
}
