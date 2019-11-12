/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 00:02:33 by hlombard          #+#    #+#             */
/*   Updated: 2019/04/02 22:16:45 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <unistd.h>

int			ft_convert_c(t_flags *flags, va_list ap)
{
	char	c;
	int		width;

	c = (char)va_arg(ap, int);
	if (flags->min_width)
	{
		if (flags->minus)
			write(1, &c, 1);
		width = 0;
		while (width++ < flags->min_width - 1)
		{
			if (flags->zero && !flags->minus)
				write(1, "0", 1);
			else
				write(1, " ", 1);
		}
	}
	if (!flags->min_width || !flags->minus)
		write(1, &c, 1);
	return (1 + (flags->min_width - 1 > 0 ? flags->min_width - 1 : 0));
}
