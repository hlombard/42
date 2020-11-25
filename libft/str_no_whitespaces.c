/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_no_whitespaces.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 12:42:47 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/25 13:36:44 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_wo_whitespaces(char *str)
{
	int i;
	int size;

	size = 0;
	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (!is_whitespace(str[i]))
			size++;
		i++;
	}
	return (size);
}

char		*str_no_whitespaces(char *str)
{
	int		i;
	int		size;
	char	*new;

	size = len_wo_whitespaces(str);
	if (!(new = ft_memalloc(size + 1)))
		return (NULL);
	i = -1;
	size = 0;
	while (str[++i])
	{
		if (!is_whitespace(str[i]))
		{
			new[size] = str[i];
			size++;
		}
	}
	new[size] = '\0';
	free(str);
	return (new);
}
