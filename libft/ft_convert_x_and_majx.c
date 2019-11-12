/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_x_and_majx.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 20:11:17 by hlombard          #+#    #+#             */
/*   Updated: 2019/04/16 16:24:50 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"
#include "libft.h"

int		ft_add_prefix(t_flags *p, int i, int *added, uintmax_t nb)
{
	if (p->hash && (p->zero || p->precision) && nb != 0 && p->precision != -1)
	{
		(p->majx) ? write(1, "0X", 2) : write(1, "0x", 2);
		*added = 2;
		i += 2;
	}
	return (i);
}

int		ft_convert_x_and_majx(t_flags *p, va_list ap)
{
	int			size;
	int			added;
	int			oldsize;
	uintmax_t	nb;
	int			i;

	if (p->precision != 0 && p->precision < p->min_width)
		p->zero = 0;
	ft_initialize_variables(&added, &i, &size, &oldsize);
	nb = va_arg(ap, uintmax_t);
	nb = ft_get_nb_u_type(p, nb);
	ft_adjust_size_x(p, &size, &oldsize, nb);
	i = ft_add_prefix(p, i, &added, nb);
	if (p->min_width && !p->minus)
		i = ft_print_min_width_no_sign_spe(p, size, i, added);
	i = ft_add_prefix2(p, i, added, nb);
	while (oldsize++ < p->precision)
		i += write(1, "0", 1);
	if (!p->majx && (p->precision != -1 || nb != 0))
		i = ft_print_x(p, i, nb);
	else if (p->majx && (p->precision != -1 || nb != 0))
		i = ft_print_maj_x(p, i, nb);
	if (p->min_width && p->minus)
		i = ft_print_additional_x(p, size, i, added);
	return (i);
}

int		ft_print_additional_x(t_flags *p, int size, int i, int added)
{
	if (added)
		i += ft_print_additional_width(p, size + 2, i);
	else
		i += ft_print_additional_width(p, size, i);
	return (i);
}

int		ft_print_x(t_flags *p, int i, uintmax_t nb)
{
	char *str;

	str = ft_itoa_sp(nb, 16, p);
	ft_putstr(str);
	i += ft_strlen(str);
	free(str);
	return (i);
}

int		ft_print_maj_x(t_flags *p, int i, uintmax_t nb)
{
	char *str;

	str = ft_itoa_base_spe_cap(nb, 16, p);
	ft_putstr(str);
	i += ft_strlen(str);
	free(str);
	return (i);
}
