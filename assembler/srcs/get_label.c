/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_label.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 23:58:26 by ratin             #+#    #+#             */
/*   Updated: 2019/09/05 16:43:02 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		compare_label(char *label1, char *label2)
{
	if (ft_strcmp(label1, label2) == 0)
		return (1);
	return (0);
}

void	trim_conv(int size, t_asm *asmbly, char **conv)
{
	if (size > 0)
		(*conv) = fill_direct(asmbly, size, conv);
	else if (size < 0)
		(*conv) = reduce_conv(asmbly, size, conv);
}

void	fill_label(t_asm *asmbly, t_instru *instru, int distance, int reverse)
{
	extern t_op	g_op_tab[17];
	int			i;
	int			size;
	char		*conv;
	char		*addr;

	i = 0;
	size = 1;
	conv = NULL;
	if (!(addr = ft_itoa(distance)))
		quit_prog(asmbly, 0);
	while (instru->conv_par[i] && instru->conv_par[i] != 'L')
		i++;
	instru->conv_par[i] == '\0' ? quit_prog(asmbly, 0) : 0;
	while (instru->conv_par[++i] && instru->conv_par[i] == 'L')
		size++;
	if (!(conv = ft_ul_convert_base(addr, "0123456789abcdef")))
		quit_prog(asmbly, 0);
	if (g_op_tab[instru->nbr_opcode - 1].direct_size == 0 && reverse == 1)
		conv = ft_strjoin_free("ffff", conv, 2);
	size -= ft_strlen(conv);
	trim_conv(size, asmbly, &conv);
	free(addr);
	write_label(instru, conv);
	free(conv);
}

void	distance_label(t_asm *asmbly, t_instru *instru, char *label)
{
	t_instru	*count;
	int			distance;
	int			reverse;

	count = instru;
	distance = 0;
	reverse = 0;
	while (count)
	{
		if (count->label != NULL)
		{
			if (compare_label(count->label, label) == 1)
				break ;
		}
		distance += count->byte_size;
		count = count->next;
		if (count == NULL)
		{
			distance = reverse_label(asmbly, instru, label);
			reverse = 1;
		}
	}
	if (count != NULL && count->added_label == 1)
		distance += count->byte_size;
	fill_label(asmbly, instru, distance, reverse);
}

void	get_label_value(t_asm *asmbly, t_instru *instru)
{
	t_param		*param;
	int			i;
	int			count;

	count = 0;
	param = instru->param;
	i = 0;
	while (instru->conv_par[i] && instru->conv_par[i] != 'L')
	{
		if (instru->conv_par[i] == ';')
			count++;
		i++;
	}
	while (count)
	{
		count--;
		param = param->next;
	}
	i = 0;
	while (param->param[i] != LABEL_CHAR)
		i++;
	i++;
	distance_label(asmbly, instru, &param->param[i]);
}
