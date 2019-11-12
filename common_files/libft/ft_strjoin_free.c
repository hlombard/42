/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 21:53:21 by hlombard          #+#    #+#             */
/*   Updated: 2019/09/04 14:15:18 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char const *s1, char const *s2, int string)
{
	char	*str;

	str = NULL;
	if (!s1)
		return (ft_strfreedup((char *)s2));
	if (!s2)
		return (ft_strfreedup((char *)s1));
	if ((str = (char *)ft_memalloc(sizeof(char) *
					(ft_strlen(s1) + ft_strlen(s2) + 1))) == NULL)
	{
		free((void *)s1);
		free((void *)s2);
		return (0);
	}
	ft_strcpy(str, s1);
	ft_strcat(str, s2);
	if (string == 1 || string == 3)
		free((void *)s1);
	if (string == 2 || string == 3)
		free((void *)s2);
	return (str);
}
