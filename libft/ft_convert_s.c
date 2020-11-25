/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_s.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 21:24:27 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/31 00:26:43 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int		ft_convert_s(t_flags *flags, va_list ap)
{
	char	*s;
	int		size;
	int		i;

	i = 0;
	s = va_arg(ap, char*);
	if (flags->precision == -1 && flags->min_width == 0)
		return (0);
	if (s == NULL && flags->precision != -1)
		s = "(null)";
	else if (s == NULL && flags->precision == -1)
	{
		write(flags->fd, " ", 1);
		return (1);
	}
	size = ft_strlen(s);
	if (flags->precision > 0 && size > 0 && flags->precision < size)
		size = size - (size - flags->precision);
	i = ft_first_part_s(flags, s, i, size);
	if (flags->precision != -1 && (!flags->min_width || !flags->minus))
	{
		ft_putnstr_fd(flags->fd, s, size);
		i += size;
	}
	return (i);
}

int		ft_first_part_s(t_flags *flags, char *s, int i, int size)
{
	int width;

	width = 0;
	if (flags->min_width)
	{
		if (flags->minus)
		{
			ft_putnstr_fd(flags->fd, s, size);
			i += size;
		}
		if (flags->precision != -1)
		{
			while (width++ < flags->min_width - size)
			{
				if (flags->zero && !flags->minus)
					i += write(flags->fd, "0", 1);
				else
					i += write(flags->fd, " ", 1);
			}
		}
		else
			while (width++ < flags->min_width)
				i += write(flags->fd, " ", 1);
	}
	return (i);
}
