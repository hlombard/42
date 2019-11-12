/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instru_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 22:54:44 by ratin             #+#    #+#             */
/*   Updated: 2019/09/05 16:41:28 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char			*get_result(t_asm *asmbly, t_param *param, t_instru **instru
	, char **result)
{
	if (param->type == 1)
	{
		if (!((*result) = ft_strjoin_free((*result), reg_conver(asmbly
			, param), 3)))
			quit_prog(asmbly, 0);
	}
	if (param->type == 2)
	{
		if (!((*result) = ft_strjoin_free((*result), dir_conver(asmbly, param
			, *instru), 3)))
			quit_prog(asmbly, 0);
	}
	if (param->type == 4)
	{
		if (!((*result) = ft_strjoin_free((*result), ind_conver(asmbly, param
			, *instru), 3)))
			quit_prog(asmbly, 0);
	}
	if (!((*result) = ft_strjoin_free((*result), ";", 1)))
		quit_prog(asmbly, 0);
	return (*result);
}

char			*convert_params(t_asm *asmbly, t_instru **instru)
{
	t_param		*param;
	char		*result;

	param = NULL;
	result = NULL;
	if (!(result = (char *)ft_memalloc(sizeof(char))))
		quit_prog(asmbly, 0);
	param = (*instru)->param;
	while (param)
	{
		result = get_result(asmbly, param, instru, &result);
		param = param->next;
	}
	return (result);
}
