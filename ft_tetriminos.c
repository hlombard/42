/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tetriminos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 22:05:20 by hlombard          #+#    #+#             */
/*   Updated: 2019/01/07 16:50:08 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "fillit.h"
#include <stdlib.h>

void			get_xmin_xmax_ymin_ymax(int coord[4], char **s, int *y, int *x)
{
	if (s[*y][*x] == '#')
	{
		if (*x < coord[0])
			coord[0] = *x;
		if (*x > coord[1])
			coord[1] = *x;
		if (*y < coord[2])
			coord[2] = *y;
		if (*y > coord[3])
			coord[3] = *y;
	}
}

void			get_tetrimino_coord(int coord[4], char **s)
{
	int x;
	int y;

	x = 0;
	y = 0;
	coord[0] = 3;
	coord[1] = 0;
	coord[2] = 3;
	coord[3] = 0;
	while (s[y] != 0)
	{
		while (s[y][x])
		{
			get_xmin_xmax_ymin_ymax(coord, s, &y, &x);
			x++;
		}
		x = 0;
		y++;
	}
}

void			tetrimino_with_coord(char tet[5][5], char **tetrimino,
		int coord[4])
{
	int i;
	int j;
	int x;
	int y;

	i = coord[0];
	j = coord[2];
	x = 0;
	y = 0;
	while (j <= coord[3])
	{
		while (i <= coord[1])
		{
			tet[y][x] = tetrimino[j][i];
			x++;
			i++;
		}
		tet[y][x] = '\0';
		x = 0;
		i = coord[0];
		j++;
		y++;
	}
	ft_strcpy(tet[y], "0");
}

t_tetriminos	*lsttetriminos(char tet[5][5], char letter)
{
	t_tetriminos	*tmp;
	int				i;

	if (!(tmp = (t_tetriminos *)malloc(sizeof(t_tetriminos))))
		return (NULL);
	tmp->letter = letter;
	tmp->placed = 0;
	tmp->coord[0] = 0;
	tmp->coord[1] = 0;
	if (!tet)
		ft_strcpy(tmp->tet[0], NULL);
	else
	{
		i = 0;
		while (ft_strcmp(tet[i], "0"))
		{
			ft_strcpy(tmp->tet[i], tet[i]);
			i++;
		}
		ft_strcpy(tmp->tet[i], tet[i]);
	}
	tmp->next = NULL;
	return (tmp);
}
