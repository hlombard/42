/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:12:35 by hlombard          #+#    #+#             */
/*   Updated: 2019/11/28 18:14:48 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_3_numbers(t_check *check)
{
	int i;

	i = check->size_a - 1;
	if (check->list_a[i] == biggest(1, check))
	{
		if (check->list_a[i - 1] == smallest(1, check))
			rotate_a(check, 1);
		else
		{
			swap_a(check, 1);
			rev_rotate_a(check, 1);
		}
	}
	else if (check->list_a[i] != biggest(1, check) && check->list_a[i]
			!= smallest(1, check))
	{
		check->list_a[i - 1] == biggest(1, check) ?
			rev_rotate_a(check, 1) : swap_a(check, 1);
	}
	else
	{
		swap_a(check, 1);
		rotate_a(check, 1);
	}
}

void	sort_first_stack(t_check *check)
{
	int i;

	i = check->size_a - 1;
	if (check->list_a[i] == biggest(1, check))
	{
		if (check->list_a[i - 1] != smallest(1, check))
		{
			swap_a(check, 1);
		}
	}
	else if (check->list_a[i] != biggest(1, check) && check->list_a[i]
			!= smallest(1, check))
	{
		if (check->list_a[i - 1] != biggest(1, check))
		{
			swap_a(check, 1);
		}
	}
	else
	{
		swap_a(check, 1);
	}
}

void	sort_4_5_numbers(t_check *check)
{
	while (check->size_a > 3)
		push_b(check, 1);
	if (!is_sorted(check))
		sort_first_stack(check);
	while (check->size_b != 0)
	{
		if (check->list_a[check->size_a - 1]
				== right_place_a(check->list_b[check->size_b - 1], check))
			push_a(check, 1);
		else
			rotate_a(check, 1);
	}
	while (!is_sorted(check))
	{
		if (smallest(1, check) == check->list_a[0])
			rev_rotate_a(check, 1);
		else if (smallest(1, check) == check->list_a[1])
		{
			rev_rotate_a(check, 1);
			rev_rotate_a(check, 1);
		}
		else
			rotate_a(check, 1);
	}
}
