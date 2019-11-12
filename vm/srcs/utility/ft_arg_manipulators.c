/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_manipulators.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:18:30 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 14:20:15 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int					ft_check_reg_index(t_corewar *cor, t_plst *plst,
		t_arg arg)
{
	int		i;

	i = 0;
	while (i < arg.nb_arg)
	{
		if (arg.type[i] == REG_CODE
				&& (arg.value[i] < 1 || arg.value[i] > REG_NUMBER))
		{
			ft_verbosity_adv(cor, plst);
			return (FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

void				ft_get_reg_value(t_arg *arg, t_plst *plst, int pos)
{
	int		i;
	int		flag;

	i = 0;
	flag = 1;
	while (i < arg->nb_arg)
	{
		if (pos & flag && arg->type[i] == REG_CODE)
		{
			arg->value[i] = plst->p.reg[arg->value[i]];
			arg->type[i] = IND_CODE;
		}
		flag = flag << 1;
		i++;
	}
}

static inline void	ft_get_ind(t_corewar *cor, t_plst *plst,
		t_arg *arg, int i)
{
	unsigned int	j;
	int				pos;

	j = 0;
	pos = arg->addr_restrict == 1
		? ft_get_restricted_addr(arg->value[i], HALF)
		: pc_modulo(arg->value[i]);
	arg->value[i] = 0;
	while (j < 4)
	{
		arg->value[i] = (arg->value[i] << 8);
		arg->value[i] += cor->arena[pc_modulo(plst->p.og_pc + pos + j)];
		j++;
	}
}

static inline void	ft_get_arg(t_corewar *cor, t_plst *plst,
		t_arg *arg, int i)
{
	unsigned int	j;

	j = 0;
	arg->value[i] = 0;
	while (j < arg->size[i])
	{
		arg->value[i] = (arg->value[i] << 8);
		arg->value[i] += cor->arena[plst->p.pc];
		if (arg->size[i] == 2)
			arg->value[i] = (short)arg->value[i];
		pc_modulo2(plst, 1);
		j++;
	}
	if (arg->type[i] == IND_CODE && plst->p.opcode != 3)
		ft_get_ind(cor, plst, arg, i);
}

void				ft_get_args(t_corewar *cor, t_plst *plst, t_arg *arg)
{
	int		i;

	i = 0;
	while (i < arg->nb_arg)
	{
		ft_get_arg(cor, plst, arg, i);
		i++;
	}
}
