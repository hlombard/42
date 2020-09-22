/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 23:26:18 by hlombard          #+#    #+#             */
/*   Updated: 2020/09/14 19:02:11 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void		ft_get_format(char **str, t_flags *p, va_list ap)
{
	ft_init_flags(p);
	ft_parse_flags(str, p);
	ft_parse_min_width(str, p, ap);
	ft_parse_precision(str, p, ap);
	ft_parse_size(str, p);
}

int			ft_write(char **s, t_flags *p, va_list ap)
{
	if (*(*s) == 'd' || *(*s) == 'i')
	{
		++(*s);
		return (ft_convert_d_and_i(p, ap));
	}
	if (*(*s) == 's')
	{
		++(*s);
		return (ft_convert_s(p, ap));
	}
	if (*(*s) == 'p')
	{
		++(*s);
		return (ft_convert_p(p, ap));
	}
	if (*(*s) == 'c')
	{
		++(*s);
		return (ft_convert_c(p, ap));
	}
	else if (*(*s) == 'o' || *(*s) == '%' || *(*s) == 'x' || *(*s) == 'X'
			|| *(*s) == 'u' || *(*s) == 'b' || *(*s) == 'f' || *(*s) == 'W')
		return (ft_write2(s, p, ap));
	return (0);
}

int			ft_write2(char **s, t_flags *p, va_list ap)
{
	if (*(*s) == 'o')
	{
		++(*s);
		return (ft_convert_o(p, ap));
	}
	if (*(*s) == '%')
	{
		++(*s);
		return (ft_convert_percentage(p));
	}
	if (*(*s) == 'x')
	{
		++(*s);
		return (ft_convert_x_and_majx(p, ap));
	}
	if (*(*s) == 'X')
	{
		p->majx = 1;
		++(*s);
		return (ft_convert_x_and_majx(p, ap));
	}
	else if (*(*s) == 'u' || *(*s) == 'b' || *(*s) == 'f' || *(*s) == 'W')
		return (ft_write3(s, p, ap));
	return (0);
}

int			ft_write3(char **s, t_flags *p, va_list ap)
{
	if (*(*s) == 'u')
	{
		++(*s);
		return (ft_convert_u(p, ap));
	}
	if (*(*s) == 'b')
	{
		++(*s);
		return (ft_convert_binary(p, ap));
	}
	if (*(*s) == 'f')
	{
		++(*s);
		return (ft_convert_float(p, ap));
	}
	if (*(*s) == 'W')
	{
		++(*s);
		return (ft_convert_nb_word(p, ap));
	}
	return (0);
}

int			ft_printf(const char *format, ...)
{
	int			read;
	char		*str;
	va_list		ap;
	t_flags		p;

	ft_bzero(&p, sizeof(t_flags));
	read = 0;
	p.fd = STDOUT_FILENO;
	str = (char *)format;
	va_start(ap, format);
	while (*str)
	{
		if (*str == '%')
		{
			ft_get_format(&str, &p, ap);
			read += ft_write(&str, &p, ap);
		}
		else if (*str == '{')
			read += ft_set_colors(p.fd, &str);
		else
			read += write(p.fd, str++, 1);
	}
	va_end(ap);
	return (read);
}
