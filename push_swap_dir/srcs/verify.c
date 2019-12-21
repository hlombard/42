/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:03:14 by hlombard          #+#    #+#             */
/*   Updated: 2019/11/29 14:46:12 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	verify_arguments(int ac, char **av, t_check *check)
{
	int i;

	i = 0;
	while (++i < ac)
		if (check_argument(i, av, check) == -1)
			quit_ps("Error", 0, check);
}

int		check_argument(int ac, char **av, t_check *check)
{
	char	**tab;
	int		ret;
	int		size;

	if (av[ac][0])
	{
		size = check->size;
		tab = ft_strsplit(av[ac], ' ');
		if (tab == NULL)
			return (-1);
		ret = check_values(tab, check);
		ft_free_tab(tab);
		if (size == check->size)
			return (-1);
		return (ret);
	}
	else
		return (-1);
}

int		check_values(char **tab, t_check *check)
{
	int j;
	int i;

	j = -1;
	while (tab[++j])
	{
		i = -1;
		while (tab[j][++i])
		{
			if (i == 0)
			{
				if (check_sign(tab, j) == -1)
					return (-1);
			}
			else
			{
				if (!ft_isdigit((char)tab[j][i]))
					return (-1);
			}
		}
	}
	if (check_maxint(tab, check) == -1)
		return (-1);
	return (1);
}

int		check_sign(char **tab, int j)
{
	if (!ft_isdigit((char)tab[j][0]))
	{
		if (tab[j][0] != '+' && tab[j][0] != '-')
			return (-1);
		else
		{
			if (!tab[j][1] || !ft_isdigit((char)tab[j][1]))
				return (-1);
		}
	}
	return (1);
}

int		check_maxint(char **tab, t_check *check)
{
	int j;

	j = -1;
	while (tab[++j])
	{
		if (strmaxint(tab[j]))
			return (-1);
		else
			check->size++;
	}
	return (1);
}
