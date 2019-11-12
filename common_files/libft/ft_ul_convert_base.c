/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ul_convert_base.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 15:29:31 by saouas            #+#    #+#             */
/*   Updated: 2019/09/05 12:51:39 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long long int	give_base_nbr(char *base)
{
	return (ft_strlen(base));
}

static unsigned long long int	u_base_to_decimal(char *nbr)
{
	unsigned long long int		nbr2;

	nbr2 = 0;
	nbr2 = atoul_base(nbr, "0123456789");
	return (nbr2);
}

static char						*treat(char *base_to,
		unsigned long long int *tab, unsigned long long int *size)
{
	unsigned long long int		i;
	unsigned long long int		tmp;
	char						*ret;

	i = 0;
	tmp = 0;
	ret = NULL;
	if (!(ret = (char *)ft_memalloc(sizeof(char))))
		return (NULL);
	while (tab[1] != 0)
	{
		ret = ft_realloc(ret, (*size)++);
		tmp = tab[1] / give_base_nbr(base_to);
		ret[i] = base_to[tab[1] % give_base_nbr(base_to)];
		ret[i + 1] = '\0';
		tab[1] = tmp;
		i++;
	}
	ret[i] = '\0';
	return (ret);
	(void)size;
}

char							*ft_ul_convert_base(char *nbr,
		char *base_to)
{
	unsigned long long int		size;
	unsigned long long int		tab[3];
	char						*ret;

	size = 2;
	ret = NULL;
	tab[0] = u_base_to_decimal(nbr);
	tab[1] = u_base_to_decimal(nbr);
	tab[2] = 0;
	ret = treat(base_to, tab, &size);
	ft_reverse_str(ret, ft_strlen(ret));
	return (ret);
}
