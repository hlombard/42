/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:57:17 by hlombard          #+#    #+#             */
/*   Updated: 2019/11/29 16:30:04 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	stock_numbers(int ac, char **av, t_check *check)
{
	int		i;
	int		j;
	int		nb;
	char	**tab;

	nb = 0;
	i = 0;
	if (!(check->list_a = (int*)malloc(sizeof(int) * check->size)))
		quit_checker("Couldn't allocate list", 0, check);
	if (!(check->list_b = (int*)malloc(sizeof(int) * check->size)))
		quit_checker("Couldn't allocate list", 1, check);
	while (++i < ac)
	{
		tab = ft_strsplit(av[i], ' ');
		if (tab == NULL)
			quit_checker("Couldn't allocate with ft_strsplit", 2, check);
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

void	invert_stack(t_check *check)
{
	int *tmp;
	int j;
	int i;

	if (!(tmp = (int*)malloc(sizeof(int) * check->size)))
		quit_checker("Couldn't allocate list", 2, check);
	i = -1;
	while (++i < check->size_a)
		tmp[i] = check->list_a[i];
	i = -1;
	j = check->size_a;
	while (++i < check->size_a)
		check->list_a[i] = tmp[--j];
	free(tmp);
}

void	judge(t_check *check)
{
	int i;

	if (check->size_b != 0)
	{
		ft_putstr("KO\n");
		return ;
	}
	i = check->size_a;
	while (i-- > 1)
	{
		if (check->list_a[i] > check->list_a[i - 1])
		{
			ft_putstr("KO\n");
			return ;
		}
	}
	ft_putstr("OK\n");
}

void	print_stack(t_check *check)
{
	int i;

	i = check->size_a;
	ft_printf("\nSTACK A:\n");
	while (i-- > 0)
		ft_printf("%d\n", check->list_a[i]);
	ft_printf("\nSTACK B:\n");
	i = check->size_b;
	while (i-- > 0)
		ft_printf("%d\n", check->list_b[i]);
}
