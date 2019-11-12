/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 10:51:49 by hlombard          #+#    #+#             */
/*   Updated: 2019/04/05 14:33:32 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	char	*str1;
	char	*str2;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	str1 = (char*)s1;
	str2 = (char*)s2;
	len = ft_strlen(str1) + ft_strlen(str2);
	if ((dst = (char*)malloc(sizeof(char) * (len + 1))) == 0)
		return (NULL);
	while (*str1)
		*(dst++) = *(str1++);
	while (*str2)
		*(dst++) = *(str2++);
	*dst = '\0';
	return (dst - len);
}
