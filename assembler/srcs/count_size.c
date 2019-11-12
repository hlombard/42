/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 17:25:39 by ratin             #+#    #+#             */
/*   Updated: 2019/08/20 23:24:17 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** Get nbr of instruction for variable asmbly->size;
*/

void	count_size(t_asm *asmbly)
{
	t_instru	*instru;
	int			y;
	int			i;
	int			count;

	count = 0;
	instru = asmbly->instru;
	while (instru)
	{
		y = -1;
		i = -1;
		while (instru->conv_par != NULL && instru->conv_par[++i])
		{
			if (instru->conv_par[i] == ';')
				continue ;
			if (y % 2 == 0)
				count++;
			y++;
		}
		instru = instru->next;
	}
	asmbly->size = count;
}
