/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 21:54:29 by hlombard          #+#    #+#             */
/*   Updated: 2019/04/16 16:24:33 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"
#include "libft.h"

void			ft_init_flags(t_flags *flags)
{
	flags->minus = 0;
	flags->plus = 0;
	flags->hash = 0;
	flags->zero = 0;
	flags->space = 0;
	flags->min_width = 0;
	flags->precision = 0;
	flags->h = 0;
	flags->hh = 0;
	flags->l = 0;
	flags->ll = 0;
	flags->majx = 0;
	flags->majl = 0;
	flags->zerozero = 0;
}

void			ft_parse_flags(char **str, t_flags *flags)
{
	(*str)++;
	while ((*(*str) == '-' || *(*str) == '+' || *(*str) == '#' || *(*str) == '0'
			|| *(*str) == ' ') && ((*(*str))))
	{
		if (*(*str) == '-')
			flags->minus = 1;
		if (*(*str) == '+')
			flags->plus = 1;
		if (*(*str) == '#')
			flags->hash = 1;
		if (*(*str) == '0')
			flags->zero = 1;
		if (*(*str) == ' ')
			flags->space = 1;
		(*str)++;
	}
}

void			ft_parse_min_width(char **str, t_flags *flags, va_list ap)
{
	int len;

	len = 0;
	if (*(*str) == '*')
		ft_flag_star(flags, str, 1, ap);
	else
	{
		while (*(*str) == '0' && ((*(*str))))
			(*str)++;
		if (*(*str) >= '1' && *(*str) <= '9')
			len = ft_atoi(*str);
		while (*(*str) >= '0' && *(*str) <= '9')
			(*str)++;
		flags->min_width = len;
	}
}

void			ft_parse_precision(char **str, t_flags *flags, va_list ap)
{
	int precision;

	precision = 0;
	if (*(*str) == '.')
	{
		flags->precision = -1;
		(*str)++;
		if (*(*str) == '*')
			ft_flag_star(flags, str, 0, ap);
		else if (*(*str) >= '0' && *(*str) <= '9')
		{
			while (*(*str) == '0')
				(*str)++;
			if (*(*str) >= '1' && *(*str) <= '9')
			{
				precision = ft_atoi(*str);
				flags->precision = precision;
			}
			while (*(*str) >= '0' && *(*str) <= '9')
				(*str)++;
		}
	}
}

void			ft_parse_size(char **str, t_flags *flags)
{
	if (*(*str) == 'h' && *(*str + 1) == 'h')
	{
		(*str)++;
		flags->hh = 1;
		(*str)++;
	}
	else if (*(*str) == 'h')
	{
		flags->h = 1;
		(*str)++;
	}
	else if (*(*str) == 'l' && *(*str + 1) == 'l')
	{
		(*str)++;
		flags->ll = 1;
		(*str)++;
	}
	else if (*(*str) == 'l' || (*(*str) == 'L'))
	{
		if (*(*str) == 'L')
			flags->majl = 1;
		else
			flags->l = 1;
		(*str)++;
	}
}
