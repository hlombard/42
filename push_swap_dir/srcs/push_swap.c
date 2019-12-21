/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:11:21 by hlombard          #+#    #+#             */
/*   Updated: 2019/11/29 16:19:59 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	solve(t_check *check)
{
	if (check->size == 2)
		rotate_a(check, 1);
	else if (check->size == 3)
		sort_3_numbers(check);
	else if (check->size > 3 && check->size <= 5)
		sort_4_5_numbers(check);
	else if (check->size > 5 && check->size <= 100)
		sort_big(check, 7);
	else if (check->size > 100 && check->size <= 500)
		sort_big(check, 12);
	else
		sort_big(check, 15);
}

int		main(int ac, char **av)
{
	t_check		check;

	check.size = 0;
	check.size_b = 0;
	check.size_a = 0;
	if (ac < 2)
		return (1);
	else
	{
		verify_arguments(ac, av, &check);
		stock_numbers(ac, av, &check);
		if (!check_doubles(&check))
		{
			quit_ps("Error", 2, &check);
		}
		invert_stack(&check);
	}
	if (!is_sorted(&check))
		solve(&check);
	free(check.list_a);
	free(check.list_b);
	return (0);
}
