/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 02:55:25 by hlombard          #+#    #+#             */
/*   Updated: 2019/04/16 16:23:56 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void		ft_putnstr(char *s, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		write(1, s++, 1);
		i++;
	}
}

void		ft_putnchar(char c, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		write(1, &c, 1);
		i++;
	}
}

int			len_base(long long value, int base)
{
	int len;

	len = 0;
	if (!value)
		return (1);
	if (value < 0)
	{
		value = -value;
		if (base == 10)
			len++;
	}
	len++;
	value /= base;
	while (value)
	{
		value /= base;
		len++;
	}
	return (len);
}

void		ft_initialize_variables(int *a, int *b, int *c, int *d)
{
	*a = 0;
	*b = 0;
	*c = 0;
	*d = 0;
}

int			ft_if_special_padding(t_flags *p, char *str, int i)
{
	if (p->minus)
	{
		ft_putstr(str);
		while (p->min_width-- > 0)
			i += write(1, " ", 1);
		return (i);
	}
	else
	{
		while (p->min_width - i > 0)
			i += write(1, " ", 1);
		ft_putstr(str);
	}
	return (i);
}
