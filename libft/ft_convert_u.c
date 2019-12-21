/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_u.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 00:53:24 by hlombard          #+#    #+#             */
/*   Updated: 2019/04/16 16:24:57 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"
#include "libft.h"

int			ft_convert_u(t_flags *p, va_list ap)
{
	intmax_t	nb;
	int			size;
	int			precision;
	int			zero;
	int			i;

	i = 0;
	zero = 0;
	nb = va_arg(ap, uintmax_t);
	nb = ft_get_nb_u_type(p, nb);
	if ((nb == 0) && (p->precision == -1))
		return (0);
	ft_set_size_u(p, &precision, &size, nb);
	if (!p->minus)
		i = ft_print_min_width_no_sign(p, size, i);
	while (zero++ < precision)
		i += write(1, "0", 1);
	if ((p->precision != -1) || nb != 0)
		i = ft_write_u_nb(p, i, nb);
	if (p->minus)
	{
		ft_get_new_size(p, &size, nb);
		i += ft_print_additional_width(p, size, i);
	}
	return (i);
}

void		ft_set_size_u(t_flags *p, int *precision, int *size, uintmax_t nb)
{
	*size = len_base(nb, 10);
	if (nb == 0 && p->precision == -1)
		size = 0;
	*precision = p->precision - *size;
	*size = p->precision > *size ? p->precision : *size;
	if (p->precision != 0)
		p->zero = 0;
}

int			ft_write_u_nb(t_flags *p, int i, uintmax_t nb)
{
	char *str;

	str = ft_itoa_sp(nb, 10, p);
	ft_putstr(str);
	i += ft_strlen(str);
	free(str);
	return (i);
}

void		ft_get_new_size(t_flags *p, int *size, uintmax_t nb)
{
	char *str;

	str = NULL;
	if (p->l || p->ll || p->h || p->hh)
	{
		str = ft_itoa_sp(nb, 10, p);
		*size -= len_base(nb, 10);
		*size += ft_strlen(str);
		free(str);
	}
}
