/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 21:47:54 by hlombard          #+#    #+#             */
/*   Updated: 2018/11/15 17:06:51 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*strr;

	strr = NULL;
	while (*s)
	{
		if (*s == (char)c)
			strr = (char*)s;
		s++;
	}
	if (*s == (char)c)
		strr = (char*)s;
	return (strr);
}
