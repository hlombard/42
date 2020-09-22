/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 16:03:10 by hlombard          #+#    #+#             */
/*   Updated: 2019/07/05 16:03:27 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long		ft_atoll(char *str)
{
	short int		sign;
	long long		nbr;

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
