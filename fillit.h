/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 18:37:35 by cfargere          #+#    #+#             */
/*   Updated: 2019/01/07 17:34:07 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# define BUFF_SIZE 21

typedef struct	s_grid
{
	char	**grid;
	char	**result_grid;
	int		x;
	int		y;
	int		i;
	int		j;
}				t_grid;

typedef struct	s_tetriminos
{
	char				tet[5][5];
	int					placed;
	char				letter;
	int					coord[2];
	struct s_tetriminos	*next;
}				t_tetriminos;

/*
** ft_check.c
*/
int				check_block_form(char *str);
int				count_connections(char **s, int *y, int *x);
char			**check_valid_tetriminos(char *str);
int				is_valid_position(char **grid, int *coord, char tet[5][5],
		int size);
int				check_last_read(t_tetriminos *first, int end);

/*
** ft_grid_functions.c
*/
int				increment_grid_coord(int *coord, int size);
void			delete_grid(char **grid);
void			place_dots(int *j, int *i, char **grid, int size);
char			**create_grid(int size);
void			print_grid(char **grid);

/*
** ft_tetriminos.c
*/
void			get_xmin_xmax_ymin_ymax(int coord[4], char **s, int *y, int *x);
void			get_tetrimino_coord(int coord[4], char **s);
void			tetrimino_with_coord(char tet[5][5], char **tetrimino,
		int coord[4]);
t_tetriminos	*lsttetriminos(char tet[5][5], char letter);

/*
** ft_tetriminos2.c
*/
void			reset_tet_coord(t_tetriminos *tet);
t_tetriminos	*get_tet_routine(t_tetriminos **tetriminos, char **str,
		int *size, char *letter);
int				put_tet_in_grid(char **grid, t_tetriminos *tet, char letter,
		int size);
void			delete_tetriminos(t_tetriminos *tet);
void			remove_tet_from_grid(char **grid, t_tetriminos *tet);

/*
** ft_solver.c
*/
t_tetriminos	*read_input(char *av, int *size, t_tetriminos **tet);
int				backtracking(char **grid, t_tetriminos *first,
		t_tetriminos *tet, int size);

#endif
