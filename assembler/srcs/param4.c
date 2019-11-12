/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 13:52:25 by syzhang           #+#    #+#             */
/*   Updated: 2019/09/05 17:38:23 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			check_end_coma(t_asm *asmbly, char *str, int line)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == COMMENT_CHAR)
			return (1);
		i++;
	}
	if (str[ft_strlen(str) - 1] == SEPARATOR_CHAR)
	{
		ft_putstr_fd("Syntax error ENDLINE line ", 2);
		ft_putnbr_fd(line, 2);
		ft_putchar_fd('\n', 2);
		return (0);
	}
	return (1);
	(void)asmbly;
}

int			get_params(t_asm *asmbly, char *str, int line)
{
	t_instru	*instru;
	int			i;

	i = 0;
	if (!(instru = find_instru(asmbly, line)))
		instru = get_last_instru(asmbly);
	instru->nbr_of_params = get_nbr_of_params(instru->opcode);
	while ((str[i] != 32 && (str[i] < 9 || str[i] > 13)) && str[i])
		i++;
	if (!(check_end_coma(asmbly, str, line)))
		return (0);
	if (!(fill_params(asmbly, &instru, &str[i], line)))
		return (0);
	if (!(get_params_type(asmbly, &str[i], line)))
		return (0);
	return (1);
}

int			error_comma(t_asm *asmbly, char *str, int line, int i)
{
	if (str[i] == SEPARATOR_CHAR && str[i + 1] == SEPARATOR_CHAR)
	{
		ft_putstr_fd("Error double comma at line ", 2);
		ft_putnbr_fd(line, 2);
		ft_putchar_fd('\n', 2);
		return (0);
	}
	return (1);
	(void)asmbly;
}
