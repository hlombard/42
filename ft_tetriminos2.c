/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tetriminos2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 22:05:30 by hlombard          #+#    #+#             */
/*   Updated: 2019/01/07 15:20:44 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "fillit.h"
#include <stdlib.h>

void			reset_tet_coord(t_tetriminos *tet)
{
	while (tet)
	{
		tet->coord[0] = 0;
		tet->coord[1] = 0;
		tet = tet->next;
	}
}

t_tetriminos	*get_tet_routine(t_tetriminos **tetriminos, char **str,
		int *size, char *letter)
{
	char				tet_clean[5][5];
	static t_tetriminos	*first_el;
	int					coord[4];

	if (!first_el)
		first_el = NULL;
	if (!str)
		return (0);
	get_tetrimino_coord(coord, str);
	tetrimino_with_coord(tet_clean, str, coord);
	delete_grid(str);
	if (*tetriminos == NULL)
	{
		*tetriminos = lsttetriminos(tet_clean, *letter);
		first_el = *tetriminos;
	}
	else
	{
		(*tetriminos)->next = lsttetriminos(tet_clean, *letter);
		*tetriminos = (*tetriminos)->next;
	}
	(*size)++;
	(*letter)++;
	return (first_el);
}

int				put_tet_in_grid(char **grid, t_tetriminos *tet,
		char letter, int size)
{
	int coord[4];

	coord[0] = 0;
	coord[1] = 0;
	tet->coord[0] ? (coord[0] = tet->coord[0]) : 0;
	tet->coord[1] ? (coord[1] = tet->coord[1]) : 0;
	coord[2] = 0;
	coord[3] = 0;
	while (is_valid_position(grid, coord, tet->tet, size) == 0)
		if (increment_grid_coord(coord, size) == 0)
			return (0);
	while (ft_strcmp(tet->tet[coord[3]], "0") && (coord[2] = 0) == 0)
	{
		while (tet->tet[coord[3]][coord[2]])
		{
			if (tet->tet[coord[3]][coord[2]] != '.')
				grid[coord[1] + coord[3]][coord[0] + coord[2]] = letter;
			coord[2]++;
		}
		coord[3]++;
	}
	increment_grid_coord(coord, size);
	tet->coord[0] = coord[0];
	tet->coord[1] = coord[1];
	return (1);
}

void			remove_tet_from_grid(char **grid, t_tetriminos *tet)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (grid[j] != 0)
	{
		while (grid[j][i])
		{
			if (grid[j][i] == tet->letter)
				grid[j][i] = '.';
			i++;
		}
		i = 0;
		j++;
	}
}

void			delete_tetriminos(t_tetriminos *tet)
{
	t_tetriminos *prev;

	prev = NULL;
	while (tet)
	{
		prev = tet;
		tet = tet->next;
		free(prev);
	}
}
