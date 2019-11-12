/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 21:48:34 by hlombard          #+#    #+#             */
/*   Updated: 2018/11/22 17:31:30 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_word(char const *s, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if ((i == 0 && s[i] != c) || (s[i] != c && s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static int		ft_start_of_word(char const *s, size_t index, char c)
{
	if (index == 0 && s[index] != c)
		return (1);
	if (s[index] != c && s[index - 1] == c)
		return (1);
	return (0);
}

static void		ft_gainline(size_t *i, size_t *j, char const *s, char c)
{
	while (s[*i + *j] != c && s[*i + *j] != '\0')
		*j = *j + 1;
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	wordlen;
	char	**tab;

	wordlen = ft_count_word(s, c);
	i = 0;
	k = 0;
	tab = malloc((wordlen + 1) * sizeof(char *));
	if (!tab || !s || !c)
		return (NULL);
	while (s[i] == c)
		i++;
	while (s[i] != '\0' && (j = 0) == 0)
	{
		if (ft_start_of_word(s, i, c))
		{
			ft_gainline(&i, &j, s, c);
			tab[k++] = ft_strsub(s, i, j);
		}
		i++;
	}
	tab[k] = 0;
	return (tab);
}
