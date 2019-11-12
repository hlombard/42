/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:28:26 by hlombard          #+#    #+#             */
/*   Updated: 2018/11/14 21:43:31 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str_copy;

	str_copy = (char*)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (str_copy == NULL)
		return (NULL);
	else
		str_copy = ft_strcpy(str_copy, s1);
	return (str_copy);
}
