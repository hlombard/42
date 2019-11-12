/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfreedup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 22:08:53 by hlombard          #+#    #+#             */
/*   Updated: 2019/08/15 22:08:57 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strfreedup(char *s1)
{
	size_t			size;
	char			*dest;

	dest = NULL;
	size = ft_strlen(s1);
	if (!(dest = (char *)ft_memalloc(sizeof(*dest) * (size + 1))))
		return (NULL);
	if (dest != NULL)
		ft_strcpy(dest, s1);
	free(s1);
	return (dest);
}
