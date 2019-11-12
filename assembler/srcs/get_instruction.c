/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instruction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 16:35:31 by ratin             #+#    #+#             */
/*   Updated: 2019/09/05 16:48:27 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				treat_label(t_instru *instru, char **label, char *str)
{
	if (instru->label == NULL)
		instru->label = *label;
	if (check_opc_presence(str) == 0)
		return (-1);
	return (0);
}

int				get_label(t_asm *asmbly, char *str, int line, int i)
{
	t_instru	*instru;
	char		*label;
	int			y;

	y = 0;
	if (!(instru = find_instru(asmbly, line)))
		instru = get_last_instru(asmbly);
	while ((str[y] == 32 || (str[y] >= 9 && str[y] <= 13)) && str[y])
		y++;
	while (str[i] && str[i] != (char)LABEL_CHAR)
		i++;
	if (!(label = ft_strsub(str, y, (size_t)i)))
	{
		free(str);
		quit_prog(asmbly, 1);
	}
	if (label[ft_strlen(label) - 1] == LABEL_CHAR)
	{
		free(label);
		if (!(label = ft_strsub(str, y, (size_t)i - 1)))
			free_quit_prog(asmbly, str, 1);
	}
	verify_label(asmbly, label, line, str);
	return (treat_label(instru, &label, str));
}

static int		last_instru_cmplt(t_asm *asmbly)
{
	t_instru	*last;

	last = asmbly->instru;
	if (last == NULL)
		return (1);
	while (last->next)
		last = last->next;
	if (last->label != NULL && last->opcode == NULL)
		return (-1);
	if (last->opcode == NULL)
		return (0);
	return (1);
}

void			get_instruction(t_asm *asmbly, char *str, int line)
{
	extern t_op	g_op_tab[17];
	int			indexer;
	t_instru	*instru;
	int			op_index;

	last_instru_cmplt(asmbly) == 1 ? add_instru(asmbly, line) : 0;
	if (check_label_presence(str) == 1)
	{
		if (last_instru_cmplt(asmbly) == -1)
			add_instru(asmbly, line);
		if (get_label(asmbly, str, line, 0) == -1)
		{
			if (!(instru = find_instru(asmbly, line)))
				instru = get_last_instru(asmbly);
			return ;
		}
	}
	indexer = get_opcode(asmbly, str, line);
	if (!(instru = find_instru(asmbly, line)))
		instru = get_last_instru(asmbly);
	op_index = find_op_index(instru->opcode);
	instru->nbr_opcode = g_op_tab[op_index].opcode;
	if (!(get_params(asmbly, &str[indexer], line)))
		free_quit_prog(asmbly, str, 1);
	check_params_error(asmbly, str, line);
}
