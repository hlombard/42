/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 10:25:59 by hlombard          #+#    #+#             */
/*   Updated: 2018/11/14 22:24:32 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*new;

	new = (char*)malloc(sizeof(char) * size + 1);
	if (!new)
		return (NULL);
	ft_bzero(new, size);
	new[size] = '\0';
	return (new);
}
