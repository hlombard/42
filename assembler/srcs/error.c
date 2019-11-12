/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 20:14:55 by ratin             #+#    #+#             */
/*   Updated: 2019/09/05 16:52:59 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_error(t_asm *asmbly, char *str)
{
	ft_putstr_fd("Lexical error for", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	free(str);
	quit_prog(asmbly, 1);
}

void	p_error(t_asm *asmbly, t_param *param, int line, t_instru *ins)
{
	ft_putstr_fd("bad parameter at line: ", 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd(" for instruction ", 2);
	ft_putstr_fd(ins->opcode, 2);
	ft_putstr_fd(".\nGot ", 2);
	if (param->type == 1)
		ft_putstr_fd("register", 2);
	if (param->type == 2)
		ft_putstr_fd("direct", 2);
	if (param->type == 4)
		ft_putstr_fd("indirect", 2);
	ft_putstr_fd("\n", 2);
	quit_prog(asmbly, 1);
}
