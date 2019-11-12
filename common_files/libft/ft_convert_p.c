/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 21:34:32 by hlombard          #+#    #+#             */
/*   Updated: 2019/04/16 16:25:23 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"
#include "libft.h"

int		ft_convert_p(t_flags *f, va_list ap)
{
	int			added;
	long long	point;
	int			len;
	char		*str;

	added = 0;
	point = va_arg(ap, long long);
	len = point ? len_base(point, 16) + 2 : 3;
	if (point == 0 && f->precision == -1)
		len = 2;
	ft_set_prefix_p(f, len, &added);
	if (!added)
		write(1, "0x", 2);
	str = ft_itoa_base(point, 16);
	if (point == 0 && f->precision == -1)
		added = 3;
	else
		ft_putstr(str);
	free(str);
	if (f->min_width > len && f->minus)
		ft_putnchar(' ', f->min_width - len);
	if (f->min_width > len)
		return (f->min_width);
	return (len);
}

void	ft_set_prefix_p(t_flags *f, int len, int *added)
{
	int changed;

	changed = 0;
	if (f->precision == -1)
	{
		f->precision = 0;
		changed = 1;
	}
	if ((f->min_width > len || f->precision > len) && (!f->minus))
	{
		f->min_width = (f->min_width) ? f->min_width + 2 : f->precision + 2;
		if (f->zero || f->precision)
		{
			write(1, "0x", 2);
			ft_putnchar('0', f->min_width - len);
			*added = 1;
		}
		else
		{
			f->min_width -= 2;
			ft_putnchar(' ', (f->min_width - len));
		}
	}
	if (changed)
		f->precision = -1;
}
