/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 20:20:02 by ratin             #+#    #+#             */
/*   Updated: 2019/09/05 16:41:28 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

long long int		ft_pow(int x, unsigned int y)
{
	long long int	tmp;

	tmp = 1;
	if (y == 0)
		return (tmp);
	else
		while (y != 0)
		{
			tmp = x * tmp;
			y--;
		}
	return (tmp);
}

int					binary_to_decimal(long long n)
{
	int				decimal_number;
	int				i;
	int				remain;

	decimal_number = 0;
	i = 0;
	while (n != 0)
	{
		remain = n % 10;
		n = n / 10;
		decimal_number = decimal_number + (remain * ft_pow(2, i));
		++i;
	}
	return (decimal_number);
}

char				*fill_bincode(t_asm *asmbly, char *bin_code)
{
	while (ft_strlen(bin_code) < 8)
	{
		if (!(bin_code = ft_strjoin_free(bin_code, "00", 1)))
			quit_prog(asmbly, 0);
	}
	return (bin_code);
}

void				get_bin_code(t_asm *asmbly, t_param **param, char **bin)
{
	if ((*param)->type == 1)
	{
		if (!((*bin) = ft_strjoin_free((*bin), "01", 1)))
			quit_prog(asmbly, 0);
	}
	if ((*param)->type == 2)
	{
		if (!((*bin) = ft_strjoin_free((*bin), "10", 1)))
			quit_prog(asmbly, 0);
	}
	if ((*param)->type == 4)
	{
		if (!((*bin) = ft_strjoin_free((*bin), "11", 1)))
			quit_prog(asmbly, 0);
	}
}

char				*get_ocp(t_asm *asmbly, t_instru *instru)
{
	t_param			*param;
	int				decimal_code;
	char			*bin_code;
	char			*result;
	char			*d_code;

	param = instru->param;
	if (!(bin_code = ft_strnew(0)))
		quit_prog(asmbly, 0);
	while (param)
	{
		get_bin_code(asmbly, &param, &bin_code);
		param = param->next;
	}
	if (ft_strlen(bin_code) < 8)
		bin_code = fill_bincode(asmbly, bin_code);
	decimal_code = binary_to_decimal(ft_atoi(bin_code));
	d_code = ft_itoa(decimal_code);
	if (!(result = ft_ul_convert_base(d_code, "0123456789abcdef")))
		quit_prog(asmbly, 0);
	free(d_code);
	free(bin_code);
	return (result);
}
