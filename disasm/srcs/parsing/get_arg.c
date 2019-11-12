/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 12:45:32 by ratin             #+#    #+#             */
/*   Updated: 2019/09/05 02:04:56 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassembler.h"

static inline void	print_type(t_corewar *cor, t_arg_type arg_type)
{
	char		direct_char[1];

	direct_char[0] = DIRECT_CHAR;
	if (arg_type == REG_CODE)
		ft_putstr_fd("r", cor->fd);
	if (arg_type == DIR_CODE)
		write(cor->fd, direct_char, 1);
}

static inline void	print_value(t_corewar *cor, int value)
{
	char			*to_print;

	if (!(to_print = ft_itoa((int)value)))
		decomp_quit(cor, "Error ft_itoa\n");
	ft_putstr_fd(to_print, cor->fd);
	free(to_print);
}

static inline void	ft_get_arg(t_corewar *cor, t_arg *arg, int i)
{
	unsigned int	j;

	j = 0;
	arg->value[i] = 0;
	while (j < arg->size[i])
	{
		arg->value[i] = (arg->value[i] << 8);
		arg->value[i] += cor->code[cor->pc];
		cor->pc++;
		j++;
	}
}

void				ft_get_args(t_corewar *cor, t_arg *arg)
{
	int				i;
	char			separator[3];

	separator[0] = SEPARATOR_CHAR;
	separator[1] = ' ';
	separator[2] = '\0';
	i = 0;
	while (i < arg->nb_arg)
	{
		ft_get_arg(cor, arg, i);
		print_type(cor, arg->type[i]);
		print_value(cor, arg->value[i]);
		if (i + 1 < arg->nb_arg)
			ft_putstr_fd(separator, cor->fd);
		i++;
	}
}
