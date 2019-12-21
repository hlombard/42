/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:54:42 by hlombard          #+#    #+#             */
/*   Updated: 2019/11/29 14:58:11 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	swap_a(t_check *check, int verbose)
{
	int tmp;

	if (check->size_a < 2)
		return ;
	tmp = check->list_a[check->size_a - 1];
	check->list_a[check->size_a - 1] = check->list_a[check->size_a - 2];
	check->list_a[check->size_a - 2] = tmp;
	if (verbose == 1)
		ft_printf("sa\n");
}

void	swap_b(t_check *check, int verbose)
{
	int tmp;

	if (check->size_b < 2)
		return ;
	tmp = check->list_b[check->size_b - 1];
	check->list_b[check->size_b - 1] = check->list_b[check->size_b - 2];
	check->list_b[check->size_a - 2] = tmp;
	if (verbose == 1)
		ft_printf("sb\n");
}

void	swap_both(t_check *check, int verbose)
{
	swap_a(check, 0);
	swap_b(check, 0);
	if (verbose == 1)
		ft_printf("ss\n");
}

void	push_a(t_check *check, int verbose)
{
	if (check->size_b == 0)
		return ;
	check->list_a[check->size_a] = check->list_b[check->size_b - 1];
	check->size_a++;
	check->size_b--;
	if (verbose == 1)
		ft_printf("pa\n");
}

void	push_b(t_check *check, int verbose)
{
	if (check->size_a == 0)
		return ;
	check->list_b[check->size_b] = check->list_a[check->size_a - 1];
	check->size_b++;
	check->size_a--;
	if (verbose == 1)
		ft_printf("pb\n");
}
