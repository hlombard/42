/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_litoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 22:33:57 by hlombard          #+#    #+#             */
/*   Updated: 2019/08/15 22:34:43 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long int	len(long long int nb)
{
	long long			nb2;
	long long int		len_ret;

	nb2 = nb;
	len_ret = 0;
	if (nb2 < 0)
	{
		nb2 = nb2 * -1;
		len_ret++;
	}
	while (nb2 > 0)
	{
		nb2 = nb2 / 10;
		len_ret++;
	}
	return (len_ret);
}

static	void			count(char *str, long long *nb2, long long int *i)
{
	while (*nb2 > 0)
	{
		str[*i] = '0' + (*nb2 % 10);
		*nb2 = *nb2 / 10;
		*i -= 1;
	}
}

char					*ft_litoa(long long int nb)
{
	char				*str;
	long long int		i;
	long long			nb2;

	nb2 = nb;
	if (nb == 0)
		i = 1;
	else
		i = len(nb2);
	if (!(str = (char*)ft_memalloc(sizeof(char) * (i + 1))))
		return (NULL);
	if (nb2 == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	str[i--] = '\0';
	if (nb2 < 0)
	{
		nb2 = nb2 * -1;
		str[0] = '-';
	}
	count(str, &nb2, &i);
	return (str);
}
