/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 01:11:28 by hlombard          #+#    #+#             */
/*   Updated: 2019/04/16 16:23:52 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void		ft_flag_star(t_flags *p, char **str, int size, va_list ap)
{
	int i;

	if (*(*str) == '*')
	{
		i = va_arg(ap, int);
		if (i >= 10000)
			return ;
		if (size == 1)
		{
			p->min_width = (i < 0) ? -i : i;
			if (i < 0)
				p->minus = 1;
			if (p->zero && i < 0)
				p->zero = 0;
		}
		else
		{
			p->precision = (i < 0) ? 0 : i;
			if (i == 0)
				p->precision = -1;
		}
		(*str)++;
	}
}

int			ft_check_flags_float(t_flags *p, int *sign, int i, long double *nb)
{
	if (*sign == 1 && p->plus)
	{
		i++;
		*sign = 2;
	}
	if (*sign == 1 && !p->plus && p->space)
	{
		i += write(1, " ", 1);
	}
	if (*nb != 0)
	{
		if (p->precision == -1)
			*nb += 0.49;
	}
	return (i);
}

int			ft_neg_float(t_flags *p, long double *nb, int i, int *sign)
{
	if (*nb < 0)
	{
		*nb *= -1;
		i++;
		*sign = -1;
		if (p->space)
			p->space = 0;
		if (p->plus)
			p->plus = 0;
	}
	return (i);
}

int			ft_threat_float(unsigned long int intpart,
		long double *nb, int i, t_flags *p)
{
	i += len_base(intpart, 10);
	*nb -= intpart;
	*nb *= ft_nb_with_precision(p);
	if (*nb != 0)
		*nb += 0.49;
	return (i);
}

char		*ft_get_my_float(long double nb,
		unsigned long int intpart, t_flags *p)
{
	char	*myfloat;
	char	*decipart;

	myfloat = ft_itoa_base(intpart, 10);
	decipart = ft_itoa_sp(nb, 10, p);
	if (p->precision == -1 && !p->hash)
	{
		free(decipart);
		return (myfloat);
	}
	else
	{
		ft_strcat(myfloat, ".");
		if (p->precision == -1 && p->hash)
		{
			free(decipart);
			return (myfloat);
		}
		if (nb != 0)
			ft_strcat(myfloat, decipart);
	}
	free(decipart);
	return (myfloat);
}
