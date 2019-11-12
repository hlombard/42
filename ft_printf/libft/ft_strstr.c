/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 09:05:26 by hlombard          #+#    #+#             */
/*   Updated: 2018/11/15 13:40:56 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t		len;

	if (*needle == '\0' || ft_strlen(needle) == 0)
		return ((char*)haystack);
	len = ft_strlen(needle);
	while (*haystack)
	{
		if (ft_strncmp(haystack, needle, len) == 0)
			return ((char*)haystack);
		haystack++;
	}
	return (NULL);
}
