/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grid_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 22:04:54 by hlombard          #+#    #+#             */
/*   Updated: 2019/01/07 15:20:47 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "fillit.h"
#include "stdlib.h"

int				increment_grid_coord(int *coord, int size)
{
	if (coord[0] < size)
		coord[0]++;
	else
	{
		coord[0] = 0;
		coord[1]++;
		if (coord[1] == size)
			return (0);
	}
	return (1);
}

void			delete_grid(char **grid)
{
	int		i;

	i = 0;
	while (grid[i] != 0)
	{
		free(grid[i]);
		i++;
	}
	free(grid[i]);
	free(grid);
}

void			place_dots(int *j, int *i, char **grid, int size)
{
	while (*j < size)
	{
		while (*i < size)
		{
			grid[*j][*i] = '.';
			(*i)++;
		}
		grid[*j][*i] = '\0';
		*i = 0;
		(*j)++;
	}
}

char			**create_grid(int size)
{
	char	**grid;
	int		i;
	int		j;

	if (!(grid = (char **)malloc((size + 1) * sizeof(char *))))
		return (0);
	i = 0;
	while (i < size)
	{
		if (!(grid[i] = (char *)malloc((size + 1) * sizeof(char))))
			return (0);
		i++;
	}
	i = 0;
	j = 0;
	place_dots(&j, &i, grid, size);
	grid[j] = 0;
	return (grid);
}

void			print_grid(char **grid)
{
	int i;

	i = 0;
	while (grid[i] != 0)
	{
		ft_putstr(grid[i]);
		ft_putchar('\n');
		i++;
	}
}
