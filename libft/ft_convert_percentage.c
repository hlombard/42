/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_percentage.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 23:36:08 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/31 00:26:43 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_convert_percentage(t_flags *p)
{
	int	width;

	width = 1;
	if (p->min_width)
	{
		if (p->minus)
			write(p->fd, "%", 1);
		while (width++ < p->min_width)
		{
			if (p->zero && !p->minus)
				write(p->fd, "0", 1);
			else
				write(p->fd, " ", 1);
		}
	}
	if (!p->minus || !p->min_width)
		write(p->fd, "%", 1);
	return ((p->min_width) ? p->min_width : 1);
}
