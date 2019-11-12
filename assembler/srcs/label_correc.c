/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_correc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 08:24:07 by ratin             #+#    #+#             */
/*   Updated: 2019/09/05 16:47:25 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		move_label(t_asm *asmbly, t_instru **instru)
{
	char		*label_cpy;
	t_instru	*last;

	last = asmbly->instru;
	label_cpy = ft_strdup((*instru)->label);
	while (last->next->next)
		last = last->next;
	last->next = NULL;
	delete_instru(instru);
	last->label = label_cpy;
	last->added_label = 1;
}

void		dlt_lst_empty_lbl(t_asm *asmbly)
{
	t_instru	*instru;

	instru = asmbly->instru;
	while (instru->next)
		instru = instru->next;
	if (instru->opcode == NULL && instru->label != NULL)
		move_label(asmbly, &instru);
}

void		verify_label(t_asm *asmbly, char *label, int line, char *str)
{
	int			i;

	i = 0;
	while (label[i])
	{
		if (!(ft_strchr(LABEL_CHARS, label[i])))
		{
			ft_putstr_fd("Lexical error for label at [", 2);
			ft_putnbr_fd(line, 2);
			ft_putchar_fd(LABEL_CHAR, 2);
			ft_putnbr_fd(i, 2);
			ft_putstr_fd("] ->", 2);
			ft_putstr_fd(&label[i], 2);
			ft_putchar_fd('\n', 2);
			free(str);
			quit_prog(asmbly, 1);
		}
		i++;
	}
}

int			check_label_presence(char *str)
{
	int			i;

	i = 0;
	while ((str[i] == 32 || (str[i] >= 9 && str[i] <= 13)) && str[i])
		i++;
	while (str[i] && (ft_strchr(LABEL_CHARS, str[i]) != NULL
		|| str[i] == LABEL_CHAR))
	{
		if (str[i] == LABEL_CHAR)
			return (1);
		i++;
	}
	return (0);
}
