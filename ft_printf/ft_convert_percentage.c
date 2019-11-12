/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_percentage.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 23:36:08 by hlombard          #+#    #+#             */
/*   Updated: 2019/03/14 10:04:24 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	ft_convert_percentage(t_flags *p)
{
	int	width;

	width = 1;
	if (p->min_width)
	{
		if (p->minus)
			write(1, "%", 1);
		while (width++ < p->min_width)
		{
			if (p->zero && !p->minus)
				write(1, "0", 1);
			else
				write(1, " ", 1);
		}
	}
	if (!p->minus || !p->min_width)
		write(1, "%", 1);
	return ((p->min_width) ? p->min_width : 1);
}
