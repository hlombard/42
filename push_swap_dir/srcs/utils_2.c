/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:06:26 by hlombard          #+#    #+#             */
/*   Updated: 2019/11/28 18:07:07 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		right_place_a(int nb, t_check *check)
{
	int i;
	int best;

	if (nb > biggest(1, check))
		return (smallest(1, check));
	if (nb < smallest(1, check))
		return (smallest(1, check));
	best = biggest(1, check);
	i = -1;
	while (i++ < check->size_a - 1)
	{
		if (check->list_a[i] > nb && check->list_a[i] < best)
		{
			best = check->list_a[i];
		}
	}
	return (best);
}

int		right_place_b(int nb, t_check *check)
{
	int i;
	int best;

	if (nb > biggest(2, check))
		return (smallest(2, check));
	if (nb < smallest(2, check))
		return (smallest(2, check));
	best = biggest(2, check);
	i = -1;
	while (i++ < check->size_b - 1)
	{
		if (check->list_b[i] > nb && check->list_b[i] < best)
		{
			best = check->list_b[i];
		}
	}
	return (best);
}

int		scan_from_top(int *chunk, t_check *check)
{
	int i;
	int index_from_top;

	i = check->size_a;
	index_from_top = 0;
	while (--i >= 0)
	{
		if (check->list_a[i] >= chunk[0] && check->list_a[i] <= chunk[1])
			return (index_from_top);
		index_from_top++;
	}
	return (-1);
}

int		scan_from_bot(int *chunk, t_check *check)
{
	int i;

	i = -1;
	while (++i < check->size_a)
	{
		if (check->list_a[i] >= chunk[0] && check->list_a[i] <= chunk[1])
			return (i);
	}
	return (-1);
}

int		element_id(int nb, int stack, t_check *check)
{
	int i;

	i = -1;
	if (stack == 1)
	{
		while (++i < check->size_a)
		{
			if (check->list_a[i] == nb)
				return (i);
		}
	}
	else
	{
		while (++i < check->size_b)
		{
			if (check->list_b[i] == nb)
				return (i);
		}
	}
	return (-1);
}
