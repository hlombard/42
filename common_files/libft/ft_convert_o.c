/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_o.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 22:04:40 by hlombard          #+#    #+#             */
/*   Updated: 2019/04/16 16:25:33 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"
#include "libft.h"

uintmax_t	ft_get_nb_u_type(t_flags *p, uintmax_t nb)
{
	if (p->h)
		nb = (unsigned short int)nb;
	else if (p->hh)
		nb = (unsigned char)nb;
	else if (p->l)
		nb = (unsigned long int)nb;
	else if (p->ll)
		nb = (unsigned long long int)nb;
	else
		nb = (unsigned int)nb;
	return (nb);
}

int			ft_print_min_width_no_sign(t_flags *p, int size, int i)
{
	int width;

	width = 0;
	while (width++ < p->min_width - size)
	{
		if (p->zero && p->min_width)
			i += write(1, "0", 1);
		else
			i += write(1, " ", 1);
	}
	return (i);
}

void		ft_get_right_size_o(t_flags *p, int *size,
				int *oldsize, uintmax_t nb)
{
	if (p->precision != 0)
		p->zero = 0;
	if (p->precision >= 0 || nb > 0)
		*size = len_base(nb, 8);
	if (p->hash && (nb > 0 || p->precision < 0))
		*size = *size + 1;
	*oldsize = *size;
	*size = (p->precision > *size) ? p->precision : *size;
}

int			ft_write_o_and_free(t_flags *p, uintmax_t nb, int i)
{
	char	*str;

	str = ft_itoa_sp(nb, 8, p);
	i += ft_strlen(str);
	ft_putstr(str);
	free(str);
	return (i);
}

int			ft_convert_o(t_flags *p, va_list ap)
{
	int			size;
	int			oldsize;
	uintmax_t	nb;
	int			i;

	i = 0;
	size = 0;
	oldsize = 0;
	nb = va_arg(ap, uintmax_t);
	nb = ft_get_nb_u_type(p, nb);
	ft_get_right_size_o(p, &size, &oldsize, nb);
	if (p->min_width && !p->minus)
		i += ft_print_min_width_no_sign(p, size, i);
	if (p->hash && (nb > 0 || p->precision < 0))
		i += write(1, "0", 1);
	while (oldsize++ < p->precision)
		i += write(1, "0", 1);
	if (p->precision >= 0 || nb > 0)
		i = ft_write_o_and_free(p, nb, i);
	if (p->min_width && p->minus)
		i += ft_print_additional_width(p, size, i);
	return (i);
}
