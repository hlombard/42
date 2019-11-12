/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 22:05:12 by hlombard          #+#    #+#             */
/*   Updated: 2019/01/10 19:22:45 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "fillit.h"
#include <unistd.h>
#include <fcntl.h>

t_tetriminos		*read_input(char *av, int *size,
		t_tetriminos **tet)
{
	int				tab[3];
	char			buff[BUFF_SIZE + 1];
	char			letter;
	t_tetriminos	*first;

	tab[0] = open(av, O_RDONLY);
	letter = 'A';
	ft_bzero(buff, BUFF_SIZE + 1);
	while ((tab[1] = read(tab[0], buff, BUFF_SIZE)))
	{
		if ((tab[1] < 0) || !(check_block_form(buff)))
		{
			delete_tetriminos(first);
			return (0);
		}
		buff[tab[1]] = '\0';
		if (!(first = get_tet_routine(tet, check_valid_tetriminos(buff), size,
						&letter)))
			return (0);
		tab[2] = tab[1];
	}
	if (!(check_last_read(first, tab[2])))
		return (0);
	close(tab[0]);
	return (first);
}

int					backtracking(char **grid, t_tetriminos *first,
		t_tetriminos *tet, int size)
{
	t_tetriminos *tmp;

	tmp = first;
	if (tet == NULL)
		return (1);
	while (put_tet_in_grid(grid, tet, tet->letter, size))
	{
		tet->placed = 1;
		while (tmp && tmp->placed)
			tmp = tmp->next;
		if (backtracking(grid, first, tmp, size))
			return (1);
		else
		{
			remove_tet_from_grid(grid, tet);
			tet->placed = 0;
			tmp = first;
		}
	}
	tet->coord[0] = 0;
	tet->coord[1] = 0;
	return (0);
}

t_tetriminos		*check_input(char *arg, int *size, t_tetriminos **tet,
		char ***grid)
{
	t_tetriminos *first;

	if (!(first = read_input(arg, size, tet)))
	{
		ft_putstr("error\n");
		exit(1);
	}
	if (*size > 26)
	{
		delete_tetriminos(first);
		ft_putstr("error\n");
		exit(1);
	}
	*size = 2;
	*grid = create_grid(*size);
	*tet = first;
	return (first);
}

int					main(int ac, char **av)
{
	char			**grid;
	t_tetriminos	*tet;
	t_tetriminos	*first;
	int				size;

	size = 0;
	tet = NULL;
	if (ac == 2)
	{
		first = check_input(av[ac - 1], &size, &tet, &grid);
		tet = first;
		while (backtracking(grid, first, tet, size) == 0)
		{
			delete_grid(grid);
			size++;
			grid = create_grid(size);
			reset_tet_coord(tet);
		}
		print_grid(grid);
		delete_grid(grid);
		delete_tetriminos(tet);
	}
	else
		ft_putstr("usage: ./fillit [TETRIMINOS_LIST File (max 26 tet)]\n");
	exit(0);
}
