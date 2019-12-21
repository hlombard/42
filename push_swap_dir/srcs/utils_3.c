/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:08:56 by hlombard          #+#    #+#             */
/*   Updated: 2019/11/29 16:29:38 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_stack(t_check *check)
{
	int i;

	i = check->size_a;
	ft_printf("\nSTACK A:\n");
	while (i-- > 0)
		ft_printf("[%d]: %d\n", i, check->list_a[i]);
	ft_printf("\nSTACK B:\n");
	i = check->size_b;
	while (i-- > 0)
		ft_printf("[%d]: %d\n", i, check->list_b[i]);
}

void	stock_numbers(int ac, char **av, t_check *check)
{
	int		i;
	int		j;
	int		nb;
	char	**tab;

	nb = 0;
	i = 0;
	if (!(check->list_a = (int*)malloc(sizeof(int) * check->size)))
		quit_ps("Couldn't allocate list", 0, check);
	if (!(check->list_b = (int*)malloc(sizeof(int) * check->size)))
		quit_ps("Couldn't allocate list", 1, check);
	while (++i < ac)
	{
		tab = ft_strsplit(av[i], ' ');
		if (tab == NULL)
			quit_ps("Couldn't allocate with ft_strsplit", 2, check);
		j = -1;
		while (tab[++j])
			check->list_a[nb++] = ft_atoi(tab[j]);
		ft_free_tab(tab);
	}
	check->size_a = check->size;
	check->size_b = 0;
}

int		check_doubles(t_check *check)
{
	int i;
	int j;

	j = -1;
	while (++j < check->size)
	{
		i = j;
		while (++i < check->size)
		{
			if (check->list_a[j] == check->list_a[i])
			{
				return (0);
			}
		}
	}
	return (1);
}

void	best_setup(t_check *check, int index_2)
{
	while (check->list_b[check->size_b - 1] !=
			right_place_b(check->list_a[index_2], check) && index_2-- >= 0)
	{
		rev_rotate_both(check, 1);
	}
	if (index_2 >= 0)
	{
		while (index_2-- >= 0)
			rev_rotate_a(check, 1);
	}
}

void	move_nb(int index, int type, t_check *check)
{
	if (type == 1)
	{
		while (index-- >= 0)
			rev_rotate_a(check, 1);
		push_to_b_when_ok(check->list_a[check->size_a - 1], check);
	}
	else
	{
		while (index-- > 0)
			rotate_a(check, 1);
		push_to_b_when_ok(check->list_a[check->size_a - 1], check);
	}
}
