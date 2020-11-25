/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 00:51:22 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/24 00:51:42 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memjoin_free(void *begin, void *end, size_t len1, size_t len2)
{
	size_t	len;
	void	*joined;

	len = len1 + len2;
	if (!(joined = malloc(len)))
		return (NULL);
	ft_memcpy(joined, begin, len1);
	ft_memcpy(joined + len1, end, len2);
	free(end);
	return (joined);
}
