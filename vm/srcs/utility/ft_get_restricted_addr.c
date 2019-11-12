/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_restricted_addr.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:18:41 by gly               #+#    #+#             */
/*   Updated: 2019/09/03 14:19:26 by gly              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		ft_get_restricted_addr(int value, int flag)
{
	short	ret;

	if (value < 0 || flag == FULL)
		return (value % IDX_MOD);
	ret = (short)value;
	ret %= IDX_MOD;
	return (ret);
}
