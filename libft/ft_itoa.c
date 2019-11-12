/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:26:08 by hlombard          #+#    #+#             */
/*   Updated: 2019/03/27 13:04:49 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		nbr_len(int nb)
{
	int len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		len++;
		nb *= -1;
	}
	while (nb)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

char	*ft_itoa(int nb)
{
	long	nbr;
	int		len;
	char	*str;

	len = nbr_len(nb);
	if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len--] = '\0';
	nbr = nb;
	if (nbr == 0)
		return ("0");
	if (nbr < 0)
	{
		nbr *= -1;
		str[0] = '-';
	}
	while (nbr)
	{
		str[len--] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (str);
}
