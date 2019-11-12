/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lutoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 22:25:29 by hlombard          #+#    #+#             */
/*   Updated: 2019/08/15 22:25:39 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long long int	len(unsigned long long int nb)
{
	unsigned long long			nb2;
	unsigned long long int		len_ret;

	nb2 = nb;
	len_ret = 0;
	while (nb2 > 0)
	{
		nb2 = nb2 / 10;
		len_ret++;
	}
	return (len_ret);
}

static	void					count(char *str, unsigned long long *nb2,
		unsigned long long int *i)
{
	while (*nb2 > 0)
	{
		str[*i] = '0' + (*nb2 % 10);
		*nb2 = *nb2 / 10;
		*i -= 1;
	}
}

char							*ft_lutoa(unsigned long long int nb)
{
	char						*str;
	unsigned long long int		i;
	unsigned long long			nb2;

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
	count(str, &nb2, &i);
	return (str);
}
