/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmaxint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 16:03:51 by hlombard          #+#    #+#             */
/*   Updated: 2019/07/05 16:03:59 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		strmaxint(char *str)
{
	if (ft_strlen(str) > 11)
		return (1);
	if (ft_atoll(str) < (long)-2147483648)
		return (1);
	if (ft_atoll(str) > (long)2147483647)
		return (1);
	return (0);
}
