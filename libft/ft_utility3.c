/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 02:55:25 by hlombard          #+#    #+#             */
/*   Updated: 2020/09/15 22:26:21 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void		ft_putnstr_fd(int fd, char *s, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		write(fd, s++, 1);
		i++;
	}
}

void		ft_putnchar_fd(int fd, char c, int n)
{
	int i;

	i = 0;
	while (i < n)
	{
		write(fd, &c, 1);
		i++;
	}
}

int			len_base_u(unsigned long long value, int base)
{
	int len;

	len = 0;
	if (!value)
		return (1);
	while (value)
	{
		value /= base;
		len++;
	}
	return (len);
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
