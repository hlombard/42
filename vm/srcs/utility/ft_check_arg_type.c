/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:18:37 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 14:19:23 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_check_arg_type(t_arg arg, int i, int code1, int code2)
{
	if (arg.type[i] == code1 || arg.type[i] == code2)
		return (SUCCESS);
	else
		return (FAIL);
}
