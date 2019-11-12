/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 13:59:20 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 14:09:00 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static inline int	order_available(t_corewar *cor, int one, int two, int three)
{
	int i;

	i = -1;
	while (++i < cor->nb_players)
	{
		if (cor->process[i].order != 1)
			one++;
		if (cor->process[i].order != 2)
			two++;
		if (cor->process[i].order != 3)
			three++;
	}
	if (one == cor->nb_players)
		return (1);
	if (two == cor->nb_players)
		return (2);
	if (three == cor->nb_players)
		return (3);
	return (4);
}

void				attribute_order(t_corewar *cor)
{
	int i;
	int nb;

	i = cor->nb_players;
	while (--i >= 0)
	{
		if (cor->process[i].order == -1)
		{
			nb = order_available(cor, 0, 0, 0);
			cor->process[i].order = nb;
		}
	}
}

int					check_doubles_order(t_corewar *cor)
{
	int i;
	int j;

	i = -1;
	while (++i < cor->nb_players)
	{
		j = i;
		while (++j < cor->nb_players)
		{
			if (cor->process[i].order == cor->process[j].order
					&& cor->process[i].order != -1)
				return (0);
		}
	}
	return (1);
}

void				reorder_process(t_corewar *cor)
{
	int			i;
	int			j;
	t_process	tmp;

	i = -1;
	while (++i < cor->nb_players)
	{
		j = i;
		while (++j < cor->nb_players)
		{
			if (cor->process[i].order != -1 &&
					cor->process[i].order < cor->process[j].order)
			{
				tmp = cor->process[i];
				cor->process[i] = cor->process[j];
				cor->process[j] = tmp;
			}
		}
	}
}

uint32_t			swap_endian(uint32_t val)
{
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return ((val << 16) | (val >> 16));
}
