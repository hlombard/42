/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:10:21 by gly               #+#    #+#             */
/*   Updated: 2019/09/06 16:21:37 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	dump_option(t_corewar *cor, char **av, int *i)
{
	int		cycle;

	if (!av[*i + 1])
	{
		corewar_usage();
		corewar_quit("Need to specify N cycle after -d option");
	}
	(*i)++;
	cycle = ft_atoi(av[*i]);
	if (cycle < 0)
		cor->n_dump = -1;
	else
		cor->n_dump = cycle;
}

void	verbosity_option(t_corewar *cor, char **av, int ac, int *i)
{
	if (*i + 1 >= ac)
	{
		corewar_usage();
		corewar_quit("");
	}
	(*i)++;
	cor->v_lvl = ft_atoi(av[*i]);
	cor->verbosity = 1;
}

void	order_option(t_corewar *cor, char **av, int *i)
{
	int	order;

	if (!av[*i + 1])
	{
		corewar_usage();
		corewar_quit("\nNeed to specify [number] after -n option");
	}
	(*i)++;
	if (ft_strcmp(av[*i], "1") && ft_strcmp(av[*i], "2")
		&& ft_strcmp(av[*i], "3") && ft_strcmp(av[*i], "4"))
	{
		corewar_usage();
		corewar_quit("\n-n [number] option has to be \
				between 1 and 4 (included)");
	}
	order = ft_atoi(av[*i]);
	cor->order = order;
	cor->order_option = 1;
}
