/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 19:50:07 by ratin             #+#    #+#             */
/*   Updated: 2019/09/05 16:46:12 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_instru		*find_instru(t_asm *asmbly, int line)
{
	t_instru	*last;

	last = asmbly->instru;
	while (last)
	{
		if (last->line == line)
			return (last);
		last = last->next;
	}
	return (NULL);
}

t_instru		*create_instuction(t_asm *asmbly, int line)
{
	t_instru	*new_instru;

	if (!(new_instru = ft_memalloc(sizeof(*new_instru))))
		quit_prog(asmbly, 1);
	ft_bzero(new_instru, sizeof(new_instru));
	new_instru->conv_par = NULL;
	new_instru->param = NULL;
	new_instru->label = NULL;
	new_instru->opcode = NULL;
	new_instru->line = line;
	new_instru->nbr_of_params = 0;
	new_instru->added_label = 0;
	new_instru->byte_size = 0;
	new_instru->labelsrc = 0;
	new_instru->next = NULL;
	return (new_instru);
}

void			add_instru(t_asm *asmbly, int line)
{
	t_instru	*new_instru;
	t_instru	*last;

	last = asmbly->instru;
	new_instru = create_instuction(asmbly, line);
	if (asmbly->instru == NULL)
		asmbly->instru = new_instru;
	else
	{
		while (last->next)
			last = last->next;
		last->next = new_instru;
	}
}

void			delete_instru(t_instru **instru)
{
	free((*instru)->conv_par);
	free((*instru)->label);
	free((*instru)->opcode);
	if ((*instru)->param != NULL)
	{
		free((*instru)->param->param);
		free((*instru)->param);
	}
	free(*instru);
}

t_instru		*get_last_instru(t_asm *asmbly)
{
	t_instru	*last;

	last = asmbly->instru;
	while (last->next)
		last = last->next;
	return (last);
}
