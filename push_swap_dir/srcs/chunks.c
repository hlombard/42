/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:08:15 by hlombard          #+#    #+#             */
/*   Updated: 2019/11/28 18:08:44 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		**create_chunks(t_check *check, int nb_chunks, int i, int j)
{
	int		**chunks;

	if (!(chunks = (int**)malloc(sizeof(int*) * nb_chunks)))
		return (NULL);
	while (++j < nb_chunks)
	{
		if (!(chunks[j] = (int*)malloc(sizeof(int) * 2)))
			return (NULL);
	}
	chunks[0][0] = smallest(1, check);
	chunks[nb_chunks - 1][1] = biggest(1, check);
	i = (chunks[nb_chunks - 1][1] - chunks[0][0]) / nb_chunks;
	chunks[0][1] = smallest(1, check) + i;
	chunks[nb_chunks - 1][0] = chunks[nb_chunks - 1][1] - i;
	j = 0;
	while (++j < nb_chunks)
	{
		chunks[j][0] = chunks[j - 1][1] + 1;
		chunks[j][1] = chunks[j][0] + i;
	}
	return (chunks);
}

int		still_exists_current_chunk(int *chunk, t_check *check)
{
	int i;

	i = -1;
	while (++i < check->size_a)
	{
		if (check->list_a[i] >= chunk[0] && check->list_a[i] <= chunk[1])
			return (1);
	}
	return (0);
}

void	free_chunks(int **chunks, int nb_chunks)
{
	int i;

	i = -1;
	while (++i < nb_chunks)
		free(chunks[i]);
	free(chunks);
}
