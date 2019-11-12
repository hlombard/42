/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_utility.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:54:16 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 14:54:17 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	highlight_process_pc(t_corewar *cor)
{
	t_plst			*process;
	unsigned int	i;
	int				id;

	process = cor->plst;
	while (process)
	{
		i = process->p.og_pc;
		id = process->p.id;
		id = re_adjust_id(id, &process->p);
		highlight_it(cor, i, id);
		process = process->next;
	}
}

int		re_adjust_id(int id, t_process *pro)
{
	if (pro->order == -1)
		return (-id);
	else
		return (pro->order);
}

void	highlight_it(t_corewar *cor, unsigned int i, int id)
{
	unsigned char	c;

	c = cor->arena[i];
	if (cor->render.mem_owner[i] == 0)
		wattron(cor->render.main, COLOR_PAIR(1));
	else
		wattron(cor->render.main, COLOR_PAIR(id + 8));
	if (cor->stealth)
		mvwprintw(cor->render.main, (i / 64) + 2, (i % 64) * 3 + 3, "ff");
	else
		mvwprintw(cor->render.main, (i / 64) + 2, (i % 64) * 3 + 3, "%.2x", c);
	if (cor->render.mem_owner[i] == 0)
		wattroff(cor->render.main, COLOR_PAIR(1));
	else
		wattroff(cor->render.main, COLOR_PAIR(id + 8));
}

void	set_attributes(t_corewar *cor, unsigned char color, int i)
{
	if (color == 0)
		wattron(cor->render.main, COLOR_PAIR(7));
	else if (color == 5 && cor->render.bold[i] != 0)
		wattron(cor->render.main, COLOR_PAIR(14));
	else
		wattron(cor->render.main, COLOR_PAIR(color));
	if (cor->render.bold[i] != 0)
		wattron(cor->render.main, A_BOLD);
}

void	unset_attributes(t_corewar *cor, unsigned char color, int i)
{
	if (color == 0)
		wattroff(cor->render.main, COLOR_PAIR(7));
	else if (color == 5 && cor->render.bold[i] != 0)
		wattroff(cor->render.main, COLOR_PAIR(14));
	else
		wattroff(cor->render.main, COLOR_PAIR(color));
	if (cor->render.bold[i] != 0)
	{
		wattroff(cor->render.main, A_BOLD);
		cor->render.bold[i] -= 1;
	}
}
