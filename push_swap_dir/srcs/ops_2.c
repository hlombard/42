/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:10:27 by hlombard          #+#    #+#             */
/*   Updated: 2019/11/28 18:10:48 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate_a(t_check *check, int verbose)
{
	int tmp;
	int i;

	if (check->size_a < 2)
		return ;
	i = check->size_a;
	while (--i > 0)
	{
		tmp = check->list_a[i];
		check->list_a[i] = check->list_a[i - 1];
		check->list_a[i - 1] = tmp;
	}
	if (verbose == 1)
		ft_printf("ra\n");
}

void	rotate_b(t_check *check, int verbose)
{
	int tmp;
	int i;

	if (check->size_b < 2)
		return ;
	i = check->size_b;
	while (i-- > 1)
	{
		tmp = check->list_b[i];
		check->list_b[i] = check->list_b[i - 1];
		check->list_b[i - 1] = tmp;
	}
	if (verbose == 1)
		ft_printf("rb\n");
}

void	rotate_both(t_check *check, int verbose)
{
	rotate_a(check, 0);
	rotate_b(check, 0);
	if (verbose == 1)
		ft_printf("rr\n");
}
