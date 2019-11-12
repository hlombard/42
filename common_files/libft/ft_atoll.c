/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 16:03:10 by hlombard          #+#    #+#             */
/*   Updated: 2019/08/28 16:03:32 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

long long		remove_false_neg(long long nbr, int sign)
{
	if (nbr < 0)
	{
		if (sign == -1)
			return (-9223372036854775807 - 1);
		else
			return (9223372036854775807);
	}
	else if (sign == -1)
		return (nbr * sign);
	return (nbr);
}

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
		if ((nbr = (nbr * 10) + (*str - 48)) < 0)
			break ;
		str++;
	}
	nbr = remove_false_neg(nbr, sign);
	return (nbr);
}
