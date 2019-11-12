/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 10:51:49 by hlombard          #+#    #+#             */
/*   Updated: 2018/12/02 22:35:56 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strnew;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	strnew = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)));
	if (!strnew)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		strnew[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		strnew[i] = s2[j];
		i++;
	}
	strnew[i] = '\0';
	return (strnew);
}
