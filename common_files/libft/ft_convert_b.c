/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 23:29:55 by hlombard          #+#    #+#             */
/*   Updated: 2019/04/16 16:26:05 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"
#include "libft.h"

int		ft_convert_binary(t_flags *p, va_list ap)
{
	int			size;
	int			oldsize;
	uintmax_t	nb;
	int			i;
	char		*str;

	str = NULL;
	if (p->precision != 0)
		p->zero = 0;
	nb = va_arg(ap, uintmax_t);
	nb = ft_get_nb_u_type(p, nb);
	size = ft_get_size(p, nb, &i);
	oldsize = size;
	if (p->min_width && !p->minus)
		i = ft_print_min_width_no_sign(p, size, i);
	if (p->hash && (nb > 0 || p->precision < 0))
		i += write(1, "0", 1);
	while (oldsize++ < p->precision)
		i += write(1, "0", 1);
	if (p->precision >= 0 || nb > 0)
		ft_write_and_free(p, str, i, nb);
	if (p->min_width && p->minus)
		i += ft_print_additional_width(p, size, i);
	return (size);
}

int		ft_get_size(t_flags *p, uintmax_t nb, int *i)
{
	int size;

	*i = 0;
	size = 0;
	if (p->precision >= 0 || nb > 0)
		size = len_base(nb, 8);
	if (p->hash && (nb > 0 || p->precision < 0))
		size = size + 1;
	size = (p->precision > size) ? p->precision : size;
	return (size);
}

int		ft_write_and_free(t_flags *p, char *str, int i, uintmax_t nb)
{
	str = ft_itoa_base_spe(nb, 2, p);
	ft_putstr(str);
	i += ft_strlen(str);
	free(str);
	return (i);
}
