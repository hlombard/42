/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:26:08 by hlombard          #+#    #+#             */
/*   Updated: 2019/08/16 14:56:03 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int nb)
{
	long	nbr;
	int		len;
	char	*str;

	len = nbr_len(nb);
	if (!(str = (char*)ft_memalloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len--] = '\0';
	nbr = nb;
	if (nbr == 0)
	{
		str[0] = '0';
		return (str);
	}
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
