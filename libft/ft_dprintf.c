/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 18:58:07 by hlombard          #+#    #+#             */
/*   Updated: 2020/09/14 19:02:58 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_dprintf(int fd, const char *format, ...)
{
	int			read;
	char		*str;
	va_list		ap;
	t_flags		p;

	ft_bzero(&p, sizeof(t_flags));
	read = 0;
	p.fd = fd;
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
