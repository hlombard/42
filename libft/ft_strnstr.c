/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 21:47:35 by hlombard          #+#    #+#             */
/*   Updated: 2018/11/23 18:55:58 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t			i;
	char			*j;
	char			*k;

	if (!*needle)
		return ((char *)haystack);
	while (len-- && *haystack)
	{
		if (*haystack == *needle)
		{
			i = len;
			j = (char *)haystack + 1;
			k = (char *)needle + 1;
			while (i-- && *j && *k && *j == *k)
			{
				++j;
				++k;
			}
			if (!*k)
				return ((char *)haystack);
		}
		++haystack;
	}
	return (NULL);
}
