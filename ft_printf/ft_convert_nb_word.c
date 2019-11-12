/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_nb_word.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 20:23:21 by hlombard          #+#    #+#             */
/*   Updated: 2019/03/14 10:04:34 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int			ft_convert_nb_word(t_flags *p, va_list ap)
{
	char	*s;
	int		i;
	int		j;
	int		size;

	j = 0;
	i = 0;
	s = va_arg(ap, char*);
	if (s == NULL)
	{
		i += write(1, "0", 1);
		return (i);
	}
	i = ft_countword(s, ' ');
	size = p->min_width;
	ft_add_flags_nb_word(p, &j, size, i);
	return (j + len_base(i, 10));
}

void		ft_add_flags_nb_word(t_flags *p, int *j, int size, int i)
{
	if (!p->minus)
	{
		while (size-- > len_base(i, 10))
		{
			if (p->zero)
				*j += write(1, "0", 1);
			else
				*j += write(1, " ", 1);
		}
		ft_putnbr(i);
	}
	else
	{
		ft_putnbr(i);
		while (size-- > len_base(i, 10))
			*j += write(1, " ", 1);
	}
}
