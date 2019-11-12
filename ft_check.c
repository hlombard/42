/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 22:04:44 by hlombard          #+#    #+#             */
/*   Updated: 2019/01/07 17:30:56 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "fillit.h"

int			check_block_form(char *str)
{
	int		points;
	int		hash;
	int		newline;
	int		i;

	points = 0;
	hash = 0;
	newline = 0;
	i = 0;
	while (str[i] == '.' || str[i] == '\n' || str[i] == '#')
	{
		if (str[i] == '.')
			points++;
		if (str[i] == '#')
			hash++;
		if (str[i] == '\n' && i != 20)
			newline++;
		i++;
	}
	if (points == 12 && hash == 4 && ((i == 21) || (i == 20)) && (newline == 4))
		return (1);
	return (0);
}

int			count_connections(char **s, int *y, int *x)
{
	int conn;

	conn = 0;
	if (s[*y][*x] == '#')
	{
		if (*x < 3)
			if (s[*y][*x + 1] == '#')
				conn++;
		if (*x > 0)
			if (s[*y][*x - 1] == '#')
				conn++;
		if (*y < 3)
			if (s[*y + 1][*x] == '#')
				conn++;
		if (*y > 0)
			if (s[*y - 1][*x] == '#')
				conn++;
	}
	return (conn);
}

char		**check_valid_tetriminos(char *str)
{
	char	**s;
	int		x;
	int		y;
	int		conn;

	x = 0;
	y = 0;
	conn = 0;
	s = ft_strsplit(str, '\n');
	while (s[y] != 0)
	{
		while (s[y][x])
		{
			conn = (conn + (count_connections(s, &y, &x)));
			x++;
		}
		x = 0;
		y++;
	}
	if (conn == 6 || conn == 8)
		return (s);
	return (0);
}

int			is_valid_position(char **grid, int *coord, char tet[5][5],
		int size)
{
	while (ft_strcmp(tet[coord[3]], "0"))
	{
		while (tet[coord[3]][coord[2]])
		{
			if (((coord[1] + coord[3]) >= size) ||
						((coord[0] + coord[2]) >= size) ||
				((grid[coord[1] + coord[3]][coord[0] + coord[2]] != '.') &&
					(tet[coord[3]][coord[2]] != '.')))
			{
				coord[2] = 0;
				coord[3] = 0;
				return (0);
			}
			coord[2]++;
		}
		coord[2] = 0;
		coord[3]++;
	}
	coord[2] = 0;
	coord[3] = 0;
	return (1);
}

int			check_last_read(t_tetriminos *first, int end)
{
	if (end != 20)
	{
		delete_tetriminos(first);
		return (0);
	}
	return (1);
}
