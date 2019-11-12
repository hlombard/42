/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opcode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 21:16:00 by ratin             #+#    #+#             */
/*   Updated: 2019/09/05 16:48:04 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			check_opcode(t_asm *asmbly, char *opcode, int line, char **str)
{
	extern t_op	g_op_tab[17];
	int			i;

	i = 0;
	while (g_op_tab[i].name != NULL)
	{
		if (ft_strcmp(opcode, g_op_tab[i].name) == 0)
			return ;
		i++;
	}
	ft_putstr_fd("Lexical error at line ", 2);
	ft_putnbr_fd(line, 2);
	ft_putchar_fd('\n', 2);
	free(opcode);
	free(*str);
	quit_prog(asmbly, 1);
}

int				pass_label_char(char *str)
{
	int			i;

	i = 0;
	if (ft_strchr(str, LABEL_CHAR) != NULL)
	{
		while ((str[i] == 32 || (str[i] >= 9 && str[i] <= 13)) && str[i])
			i++;
		while (str[i] && str[i] != LABEL_CHAR)
		{
			if ((str[i] == 32 || (str[i] >= 9 && str[i] <= 13)) && str[i])
			{
				i = 0;
				break ;
			}
			i++;
		}
	}
	return (i);
}

int				get_opcode(t_asm *asmbly, char *s, int line)
{
	int			i;
	int			y;
	char		*opcode;
	t_instru	*instru;

	i = 0;
	y = 0;
	if (!(instru = find_instru(asmbly, line)))
		instru = get_last_instru(asmbly);
	i = pass_label_char(s);
	s[i] == LABEL_CHAR ? i++ : 0;
	while ((s[i] == 32 || (s[i] >= 9 && s[i] <= 13)) && s[i])
		i++;
	while (s[i] && s[i] == ' ')
		i++;
	while (s[i + y] && s[i + y] != 32 && (s[i + y] < 9 || s[i + y] > 13))
		y++;
	if (!(opcode = ft_strsub(s, i, y)))
	{
		free(s);
		quit_prog(asmbly, 1);
	}
	check_opcode(asmbly, opcode, line, &s);
	instru->opcode = opcode;
	return (i);
}

int				check_opc_presence(char *str)
{
	int			i;

	i = 0;
	while (str[i] && str[i] != LABEL_CHAR)
		i++;
	while (str[++i])
	{
		if (str[i] == COMMENT_CHAR)
			return (0);
		if (str[i] && str[i] != 32 && (str[i] < 9 || str[i] > 13))
			return (1);
	}
	return (0);
}
