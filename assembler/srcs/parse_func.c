/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 13:29:21 by ratin             #+#    #+#             */
/*   Updated: 2019/08/30 15:20:33 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			is_empty(t_asm *asmbly, char *str)
{
	int		i;

	i = 0;
	if (ft_strcmp(str, "") == 0)
		return (1);
	while (str[i])
	{
		if (str[i] != 32 && (str[i] < 9 || str[i] > 13))
			return (0);
		i++;
	}
	(void)asmbly;
	return (1);
}

int			check_comment(char *str)
{
	int		i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == COMMENT_CHAR)
		return (1);
	else
		return (0);
}

int			name_presence(char *str)
{
	int		i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (ft_strncmp(&str[i], NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) == 0)
		return (1);
	return (0);
}

int			comment_presence(char *str)
{
	int		i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (ft_strncmp(&str[i], COMMENT_CMD_STRING
		, ft_strlen(COMMENT_CMD_STRING)) == 0)
		return (1);
	return (0);
}
