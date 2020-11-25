/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 20:24:58 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/31 00:26:43 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int			ft_update_size(char *myfloat, t_flags *p,
		unsigned long long int intpart)
{
	int j;

	j = 0;
	if (p->precision == -1 && !p->hash)
		return (j);
	else if (p->precision == -1 && p->hash)
	{
		j++;
		return (j);
	}
	else
	{
		j -= len_base(intpart, 10);
		j += ft_strlen(myfloat);
		return (j);
	}
}

int			ft_float_with_minus(char *myfloat, int i, int sign, t_flags *p)
{
	if (sign == 2)
		write(p->fd, "+", 1);
	else if (sign == -1)
		write(p->fd, "-", 1);
	ft_putstr_fd(myfloat, p->fd);
	while (i < p->min_width)
		i += write(p->fd, " ", 1);
	return (i);
}

int			ft_float_without_minus(char *myfloat, int i, int sign, t_flags *p)
{
	if (p->zero)
	{
		if (sign == 2)
			write(p->fd, "+", 1);
		else if (sign == -1)
			write(p->fd, "-", 1);
	}
	while (i < p->min_width)
	{
		if (p->zero)
			i += write(p->fd, "0", 1);
		else
			i += write(p->fd, " ", 1);
	}
	if (!p->zero)
	{
		if (sign == 2)
			write(p->fd, "+", 1);
		else if (sign == -1)
			write(p->fd, "-", 1);
	}
	ft_putstr_fd(myfloat, p->fd);
	return (i);
}

int			ft_float_special(t_flags *p, long double nb, int i)
{
	char *str;

	str = NULL;
	if (nb == 1.0 / 0.0)
	{
		str = "inf";
		i = 3;
	}
	else if (nb == -1.0 / 0.0)
	{
		str = "-inf";
		i = 4;
	}
	i = ft_if_special_padding(p, str, i);
	return (i);
}

int			ft_if_special_padding(t_flags *p, char *str, int i)
{
	if (p->minus)
	{
		ft_putstr_fd(str, p->fd);
		while (p->min_width-- > 0)
			i += write(p->fd, " ", 1);
		return (i);
	}
	else
	{
		while (p->min_width - i > 0)
			i += write(p->fd, " ", 1);
		ft_putstr_fd(str, p->fd);
	}
	return (i);
}
