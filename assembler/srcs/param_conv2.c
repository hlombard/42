/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_conv2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 04:38:57 by ratin             #+#    #+#             */
/*   Updated: 2019/09/05 16:41:28 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char		*reg_conver(t_asm *asmbly, t_param *param)
{
	char		*result;
	char		*tmp;

	result = ft_convert_base_finale(&param->param[1], "0123456789abcdef");
	if (ft_strlen(result) < 2)
	{
		if (!(tmp = ft_strdup(result)))
			quit_prog(asmbly, 0);
		free(result);
		if (!(result = (char *)ft_memalloc(sizeof(char) * 3)))
			quit_prog(asmbly, 0);
		result[0] = '0';
		result[1] = tmp[0];
		result[2] = '\0';
		free(tmp);
	}
	return (result);
}
