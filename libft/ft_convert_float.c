/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_float.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 23:01:00 by hlombard          #+#    #+#             */
/*   Updated: 2019/04/16 16:25:51 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"
#include "libft.h"

int			ft_if_zero_no_minus(t_flags *p, int sign, int i, char *myfloat)
{
	if (p->zero)
	{
		if (sign == 2)
			write(1, "+", 1);
	}
	if (p->precision != -1)
		i += p->precision;
	while (i < p->min_width)
	{
		if (p->zero)
			i += write(1, "0", 1);
		else
			i += write(1, " ", 1);
	}
	if (!p->zero)
		if (sign == 2)
			write(1, "+", 1);
	ft_putstr(myfloat);
	free(myfloat);
	if (p->precision == -1)
		return (i);
	while (p->precision--)
		write(1, "0", 1);
	return (i);
}

int			ft_if_zero_float(int i, int sign, char *myfloat, t_flags *p)
{
	if (p->minus)
	{
		if (sign == 2)
			write(1, "+", 1);
		ft_putstr(myfloat);
		free(myfloat);
		if (p->precision != -1)
		{
			while (p->precision--)
				i += write(1, "0", 1);
		}
		while (i < p->min_width)
			i += write(1, " ", 1);
	}
	else if (!p->minus)
		i = ft_if_zero_no_minus(p, sign, i, myfloat);
	return (i);
}

int			ft_convert_float(t_flags *p, va_list ap)
{
	long double				nb;
	unsigned long int		intpart;
	char					*myfloat;
	int						i;
	int						sign;

	i = 0;
	sign = 1;
	nb = (p->l || p->majl) ? va_arg(ap, long double) : va_arg(ap, double);
	if (nb == 1.0 / 0.0 || nb == -1.0 / 0.0)
		return (ft_float_special(p, nb, i));
	i = ft_neg_float(p, &nb, i, &sign);
	i = ft_check_flags_float(p, &sign, i, &nb);
	intpart = (long long unsigned int)nb;
	i = ft_threat_float(intpart, &nb, i, p);
	myfloat = ft_get_my_float(nb, intpart, p);
	i += ft_update_size(myfloat, p, intpart);
	if (nb == 0)
		return (ft_if_zero_float(i, sign, myfloat, p));
	if (p->minus)
		i = ft_float_with_minus(myfloat, i, sign, p);
	else if (!p->minus)
		i = ft_float_without_minus(myfloat, i, sign, p);
	free(myfloat);
	return (i);
}

int			ft_nb_with_precision(t_flags *p)
{
	int mul;
	int i;
	int changed;

	changed = 0;
	mul = 1;
	i = 0;
	if (p->precision == 0)
		p->precision = 6;
	if (p->precision == -1)
	{
		changed = 1;
		p->precision = 1;
	}
	while (i < p->precision)
	{
		mul *= 10;
		i++;
	}
	if (changed)
		p->precision = -1;
	return (mul);
}
