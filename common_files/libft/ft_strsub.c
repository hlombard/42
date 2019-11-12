/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 10:40:55 by hlombard          #+#    #+#             */
/*   Updated: 2018/11/30 21:28:47 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*tr;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	tr = (char*)malloc(sizeof(char) * len + 1);
	if (!tr)
		return (NULL);
	tr[len] = '\0';
	while (len--)
	{
		tr[i] = s[start];
		i++;
		start++;
	}
	return (tr);
}
