/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_d_and_i.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 18:59:29 by hlombard          #+#    #+#             */
/*   Updated: 2019/04/16 16:25:58 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"
#include "libft.h"

intmax_t	ft_get_nb_type(t_flags *p, intmax_t nb)
{
	if (p->h)
		nb = (short int)nb;
	else if (p->hh)
		nb = (char)nb;
	else if (p->l)
		nb = (long int)nb;
	else if (p->ll)
		nb = (long long int)nb;
	else
		nb = (int)nb;
	return (nb);
}

int			ft_print_sign(intmax_t nb, t_flags *p, int i)
{
	if (p->plus && nb >= 0)
		i += write(1, "+", 1);
	if (nb < 0)
		i += write(1, "-", 1);
	else if (p->space && nb >= 0)
		i += write(1, " ", 1);
	return (i);
}

int			ft_print_min_width(t_flags *p, int size, intmax_t nb, int i)
{
	int width;

	width = 0;
	if (p->min_width && p->zero)
		i += ft_print_sign(nb, p, i);
	while (width++ < p->min_width - size)
	{
		if (p->zero && p->min_width)
			i += write(1, "0", 1);
		else
			i += write(1, " ", 1);
	}
	return (i);
}

int			ft_print_additional_width(t_flags *p, int size, int i)
{
	int width;

	width = 0;
	if (p->min_width)
	{
		while (width++ < p->min_width - size)
			i += write(1, " ", 1);
		if (size)
			return (i - size);
	}
	return (0);
}

int			ft_convert_d_and_i(t_flags *p, va_list ap)
{
	intmax_t	nb;
	int			size;
	int			precision;
	int			i;

	i = 0;
	nb = va_arg(ap, intmax_t);
	nb = ft_get_nb_type(p, nb);
	size = len_base((nb < 0 ? -nb : nb), 10);
	if (nb == 0 && p->precision == -1)
		size = 0;
	precision = p->precision - size;
	size = p->precision > size ? p->precision : size;
	size += (nb >= 0 && (p->plus || p->space));
	if (nb < 0)
		size += 1;
	ft_adjust_flags(p, nb);
	if (!p->minus)
		i = ft_print_min_width(p, size, nb, i);
	i = ft_show_d_and_i(p, i, precision, nb);
	if (p->minus)
		i += ft_print_additional_width(p, size, i);
	return (i);
}
