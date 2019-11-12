/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 01:55:35 by hlombard          #+#    #+#             */
/*   Updated: 2019/04/16 16:24:08 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"
#include "libft.h"

int		ft_show_d_and_i(t_flags *p, int i, int precision, intmax_t nb)
{
	char	*str;
	int		zero;

	str = NULL;
	zero = 0;
	if ((p->min_width && (p->minus || !p->zero)) || !p->min_width)
		i = ft_print_sign(nb, p, i);
	while (zero++ < precision)
		i += write(1, "0", 1);
	if ((p->precision != -1) || nb != 0)
	{
		str = ft_itoa_base_spe((nb < 0 ? -nb : nb), 10, p);
		ft_putstr(str);
		i += len_base((nb < 0 ? -nb : nb), 10);
		free(str);
	}
	return (i);
}

void	ft_adjust_flags(t_flags *p, intmax_t nb)
{
	if (nb >= 0 && p->plus)
		p->space = 0;
	if (p->precision != 0)
		p->zero = 0;
}

int		ft_add_prefix2(t_flags *p, int i, int added, uintmax_t nb)
{
	if (p->hash && added == 0 && nb != 0)
	{
		(p->majx) ? write(1, "0X", 2) : write(1, "0x", 2);
		i += 2;
	}
	return (i);
}

int		ft_print_min_width_no_sign_spe(t_flags *p, int size, int i, int added)
{
	int width;

	width = 0;
	while (width++ + added < p->min_width - size)
	{
		if (p->zero && p->min_width)
			i += write(1, "0", 1);
		else
			i += write(1, " ", 1);
	}
	return (i);
}

void	ft_adjust_size_x(t_flags *p, int *size, int *oldsize, uintmax_t nb)
{
	*size = len_base(nb, 16);
	if (p->hash && nb > 0 && (p->precision == 0 || p->precision == -1) &&
			!p->minus && !p->zero)
		*size = *size + 2;
	*oldsize = *size;
	*size = (p->precision > *size) ? p->precision : *size;
	if (p->precision == -1 && nb == 0)
		*size = 0;
}
