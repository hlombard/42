/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_map2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 21:30:33 by hlombard          #+#    #+#             */
/*   Updated: 2019/04/01 13:19:51 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		ft_get_map(t_parse *f, t_fdf *p)
{
	if (f->ac == 2)
	{
		ft_printf("{cyan}{bold}Default window set : 1920x1080{eoc}\n");
		p->width = 1920;
		p->height = 1080;
	}
	else if (f->ac == 4)
		ft_check_window_size(f, p);
	else if (f->ac != 2 && f->ac != 4)
		return (ft_usage());
	if ((f->fd = open(f->av[1], O_RDONLY)) == -1)
	{
		ft_printf("{red}Couldn't open file, check usage: ./fdf{eoc}\n");
		return (0);
	}
	if (ft_check_file(f, p) == -1 || ft_stock_map(f, p) == -1)
	{
		ft_printf("{red}{bold}/!/ Not a valid file /!/{eoc}\n");
		return (0);
	}
	return (1);
}

int		ft_stock_map(t_parse *f, t_fdf *p)
{
	p->file_xmax = 0;
	while (get_next_line(f->fd, &f->line) > 0)
	{
		f->map_x = ft_strsplit(f->line, ' ');
		if (!(p->map[f->y] = malloc(sizeof(int) * ft_size_tab(f->map_x))))
			return (-1);
		if (f->verif == -1)
		{
			p->file_xmax = ft_size_tab(f->map_x);
			f->verif = 0;
		}
		if (p->file_xmax != ft_size_tab(f->map_x))
			return (-1);
		f->x = 0;
		while (f->map_x[f->x])
		{
			p->map[f->y][f->x] = ft_atoi(f->map_x[f->x]);
			free(f->map_x[f->x++]);
		}
		free(f->line);
		free(f->map_x);
		f->y++;
	}
	free(f->line);
	return (0);
}

int		ft_check_chars(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] >= 'g' && s[i] <= 'w') ||
				(s[i] >= 'G' && s[i] <= 'W') ||
				(s[i] > 'x' && s[i] <= 'z') ||
				(s[i] > 'X' && s[i] <= 'Z'))
			return (-1);
		i++;
	}
	return (0);
}

int		ft_check_file(t_parse *f, t_fdf *p)
{
	p->file_y = 0;
	while (get_next_line(f->fd, &f->line) > 0)
	{
		if (ft_check_chars(f->line) == -1)
			return (-1);
		p->file_y++;
		free(f->line);
		if (p->file_y > 10000)
			return (-1);
	}
	p->map = (int**)malloc(sizeof(int*) * p->file_y);
	if (!p->map)
		return (-1);
	close(f->fd);
	if ((f->fd = open(f->av[1], O_RDONLY)) == -1)
		return (-1);
	return (0);
}

int		ft_size_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
