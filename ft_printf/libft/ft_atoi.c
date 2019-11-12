/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 22:57:54 by hlombard          #+#    #+#             */
/*   Updated: 2018/11/22 15:01:17 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	short int			sign;
	unsigned long		nbr;

	sign = 1;
	nbr = 0;
	while (*str == '\f' || *str == '\r' || *str == '\n'
	|| *str == ' ' || *str == '\t' || *str == '\v')
		str++;
	if ((*str == 45) || (*str == 43))
	{
		if (*str == 45)
			sign = -1;
		str++;
	}
	while (ft_isdigit((int)*str))
	{
		nbr = (nbr * 10 + *str - 48);
		str++;
	}
	return (sign * nbr);
}
