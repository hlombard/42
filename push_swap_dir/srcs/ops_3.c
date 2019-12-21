/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:10:56 by hlombard          #+#    #+#             */
/*   Updated: 2019/11/28 18:11:06 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rev_rotate_a(t_check *check, int verbose)
{
	int tmp;
	int i;

	if (check->size_a < 2)
		return ;
	i = -1;
	while (++i < check->size_a - 1)
	{
		tmp = check->list_a[i];
		check->list_a[i] = check->list_a[i + 1];
		check->list_a[i + 1] = tmp;
	}
	if (verbose == 1)
		ft_printf("rra\n");
}

void	rev_rotate_b(t_check *check, int verbose)
{
	int tmp;
	int i;

	if (check->size_b < 2)
		return ;
	i = -1;
	while (++i < check->size_b - 1)
	{
		tmp = check->list_b[i];
		check->list_b[i] = check->list_b[i + 1];
		check->list_b[i + 1] = tmp;
	}
	if (verbose == 1)
		ft_printf("rrb\n");
}

void	rev_rotate_both(t_check *check, int verbose)
{
	rev_rotate_a(check, 0);
	rev_rotate_b(check, 0);
	if (verbose == 1)
		ft_printf("rrr\n");
}
