/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 18:08:04 by hlombard          #+#    #+#             */
/*   Updated: 2019/04/16 16:24:38 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int		ft_write4(char **s)
{
	++(*s);
	if (*(*s) == '1')
	{
		++(*s);
		return (ft_draw());
	}
	else if (*(*s) == '2')
	{
		++(*s);
		return (ft_draw2());
	}
	return (0);
}

int		ft_draw(void)
{
	ft_putstr("                (`.              \n");
	ft_putstr("                 \\ `.           \n");
	ft_putstr("                 )  `._..---._\n");
	ft_putstr("\\`.       __...---`         o  )\n");
	ft_putstr(" \\ `._,--'           ,    ___,'\n");
	ft_putstr("  ) ,-._          \\  )   _,-' \n");
	ft_putstr(" /,'    ``--.._____\\/--''  \n");
	return (0);
}

int		ft_draw2(void)
{
	ft_putstr("(\"`-''-/\").___..--''\"`-._ \n");
	ft_putstr(" `6_ 6  )   `-.  (     ).`-.__.`) \n");
	ft_putstr(" (_Y_.)'  ._   )  `._ `. ``-..-' \n");
	ft_putstr("   _..`--'_..-_/  /--'_.'\n");
	ft_putstr("  ((((.-''  ((((.'  (((.-' \n");
	return (0);
}
