/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 22:08:51 by ratin             #+#    #+#             */
/*   Updated: 2019/09/05 17:34:49 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_param			*create_param(t_asm *asmbly, int line, char *param)
{
	t_param		*new_param;

	if (!(new_param = (t_param *)ft_memalloc(sizeof(t_param))))
		quit_prog(asmbly, 0);
	new_param->line = line;
	new_param->param = ft_strdup(param);
	new_param->next = NULL;
	return (new_param);
}

void			add_free_param(t_asm *asmbly, t_instru **instru, int line
	, char **param)
{
	add_param(asmbly, *instru, line, *param);
	free(*param);
}

void			add_param(t_asm *asmbly, t_instru *instru
	, int line, char *param)
{
	t_param		*new_param;
	t_param		*last;

	last = instru->param;
	new_param = create_param(asmbly, line, param);
	if (instru->param == NULL)
		instru->param = new_param;
	else
	{
		while (last->next)
			last = last->next;
		last->next = new_param;
	}
}
