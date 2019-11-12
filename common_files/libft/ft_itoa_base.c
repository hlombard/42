/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 12:56:42 by hlombard          #+#    #+#             */
/*   Updated: 2019/08/06 18:17:27 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_getlen(int value, int base)
{
	int len;

	len = 0;
	if (value == 0)
		return (1);
	if (value < 0)
	{
		if (base == 10)
			len++;
		value *= -1;
	}
	while (value)
	{
		len++;
		value /= base;
	}
	return (len);
}

char	*ft_itoa_base(int value, int base)
{
	char	*str;
	char	*basestring;
	long	nb;
	int		len;

	basestring = "0123456789ABCDEF";
	len = ft_getlen(value, base);
	str = (char*)ft_memalloc(sizeof(char) * (len + 1));
	str[len--] = '\0';
	nb = value;
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		if (base == 10)
			str[0] = '-';
		nb *= -1;
	}
	while (nb)
	{
		str[len--] = basestring[nb % base];
		nb /= base;
	}
	return (str);
}
