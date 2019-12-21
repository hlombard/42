/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:07:20 by hlombard          #+#    #+#             */
/*   Updated: 2019/12/09 17:50:11 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	quit_ps(char *str, int type, t_check *check)
{
	if (type > 0)
		free(check->list_a);
	if (type > 1)
		free(check->list_b);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	exit(-1);
}

void	invert_stack(t_check *check)
{
	int *tmp;
	int j;
	int i;

	if (!(tmp = (int*)malloc(sizeof(int) * check->size)))
		quit_ps("Couldn't allocate list", 2, check);
	i = -1;
	while (++i < check->size_a)
		tmp[i] = check->list_a[i];
	i = -1;
	j = check->size_a;
	while (++i < check->size_a)
		check->list_a[i] = tmp[--j];
	free(tmp);
}

int		is_sorted(t_check *check)
{
	int	i;

	i = check->size_a;
	if (check->size == 1)
		return (1);
	else
	{
		while (i-- > 1)
		{
			if (check->list_a[i] > check->list_a[i - 1])
			{
				return (0);
			}
		}
		return (1);
	}
}

int		biggest(int stack, t_check *check)
{
	int i;
	int j;

	i = 0;
	j = stack == 1 ? check->list_a[0] : check->list_b[0];
	if (stack == 1)
	{
		while (i++ < check->size_a - 1)
			if (check->list_a[i] > j)
				j = check->list_a[i];
	}
	else
	{
		while (i++ < check->size_b - 1)
			if (check->list_b[i] > j)
				j = check->list_b[i];
	}
	return (j);
}

int		smallest(int stack, t_check *check)
{
	int i;
	int j;

	i = 0;
	j = stack == 1 ? check->list_a[0] : check->list_b[0];
	if (stack == 1)
	{
		while (i++ < check->size_a - 1)
			if (check->list_a[i] < j)
				j = check->list_a[i];
	}
	else
	{
		while (i++ < check->size_b - 1)
			if (check->list_b[i] < j)
				j = check->list_b[i];
	}
	return (j);
}
