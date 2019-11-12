/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plst_manipulators.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:18:49 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 14:19:32 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "vm.h"

t_plst	*ft_plst_init(t_corewar *cor)
{
	int			i;
	t_plst		*plst;
	t_plst		*elem;

	i = 0;
	plst = NULL;
	while (i < cor->nb_players)
	{
		if (!(elem = malloc(sizeof(t_plst))))
			return (NULL);
		ft_memcpy(&(elem->p), cor->process + i, sizeof(t_process));
		elem->next = plst;
		plst = elem;
		i++;
		plst->p.id = plst->p.order == -1 ? i : plst->p.order;
		plst->n_plst = i;
		plst->p.id *= -1;
		plst->p.reg[1] = plst->p.id;
	}
	cor->nb_process = i;
	cor->nb_process_max = i;
	return (plst);
}
