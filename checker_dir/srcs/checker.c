/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 13:03:03 by hlombard          #+#    #+#             */
/*   Updated: 2019/12/09 17:49:28 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	quit_checker(char *str, int type, t_check *check)
{
	if (type > 0)
		free(check->list_a);
	if (type > 1)
		free(check->list_b);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	exit(-1);
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
			quit_checker("Error", 2, &check);
		}
		invert_stack(&check);
		read_ops(&check);
		judge(&check);
	}
	free(check.list_a);
	free(check.list_b);
	return (0);
}
