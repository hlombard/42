/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 19:12:31 by hlombard          #+#    #+#             */
/*   Updated: 2019/04/16 16:26:11 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"
#include "libft.h"

int		ft_right_color(char **str, char *color, int size)
{
	int i;

	i = 0;
	ft_putstr(color);
	while (i <= size)
	{
		i++;
		(*str)++;
	}
	return (0);
}

int		ft_set_colors(char **str)
{
	if (ft_strncmp((const char *)*str, "{red}", 5) == 0)
		return (ft_right_color(str, C_RED, 4));
	else if (ft_strncmp((const char *)*str, "{green}", 7) == 0)
		return (ft_right_color(str, C_GREEN, 6));
	else if (ft_strncmp((const char *)*str, "{bold}", 6) == 0)
		return (ft_right_color(str, C_BOLD, 5));
	else if (ft_strncmp((const char *)*str, "{blue}", 6) == 0)
		return (ft_right_color(str, C_BLUE, 5));
	else if (ft_strncmp((const char *)*str, "{magenta}", 9) == 0)
		return (ft_right_color(str, C_MAGENTA, 8));
	else if (ft_strncmp((const char *)*str, "{cyan}", 6) == 0)
		return (ft_right_color(str, C_CYAN, 5));
	else if (ft_strncmp((const char *)*str, "{eoc}", 5) == 0)
		return (ft_right_color(str, C_NONE, 4));
	else
	{
		++(*str);
		return (write(1, "{", 1));
	}
}
