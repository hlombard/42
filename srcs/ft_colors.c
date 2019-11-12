/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 15:06:21 by hlombard          #+#    #+#             */
/*   Updated: 2019/03/28 22:19:41 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

double		ft_percent(int start, int end, int current)
{
	double		placement;
	double		distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

int			ft_get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int			ft_get_color(t_fdf *p, int x, int y)
{
	int			red;
	int			green;
	int			blue;
	double		percentage;

	if (p->dx > p->dy)
		percentage = ft_percent(p->x0, p->x1, x);
	else
		percentage = ft_percent(p->y0, p->y1, y);
	red = ft_get_light((p->color_0 >> 16) & 0xFF,
			(p->color_1 >> 16) & 0xFF, percentage);
	green = ft_get_light((p->color_0 >> 8) & 0xFF,
			(p->color_1 >> 8) & 0xFF, percentage);
	blue = ft_get_light(p->color_0 & 0xFF,
			p->color_1 & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}

void		ft_point_color(int *color, int z)
{
	if (z < 0)
		*color = 0x9932CC;
	if (0 == z)
		*color = 0x2085E3;
	if (1 <= z && z <= 2)
		*color = 0xE9E913;
	if (3 <= z && z <= 5)
		*color = 0xFF7800;
	if (6 <= z && z <= 8)
		*color = 0xFF0000;
	if (9 <= z && z <= 10)
		*color = 0x802A2A;
	if (11 <= z && z <= 15)
		*color = 0xA56038;
	if (16 <= z && z <= 9999)
		*color = 0x5C3F25;
}

void		ft_add_menu(t_fdf *p)
{
	mlx_string_put(p->mlx, p->win, 25, 25, 0xffffffff, \
			"Press the following Keys to interact \
		with the drawing :");
	mlx_string_put(p->mlx, p->win, 25, 60, 0xffffffff, \
			"C : Clear the window");
	mlx_string_put(p->mlx, p->win, 25, 80, 0xffffffff, \
				"P : Parallel projection");
	mlx_string_put(p->mlx, p->win, 25, 100, 0xffffffff, \
			"I : Isometric projection");
	mlx_string_put(p->mlx, p->win, 25, 120, 0xffffffff, \
			"Up Arrow : Zoom in");
	mlx_string_put(p->mlx, p->win, 25, 140, 0xffffffff, \
			"Down Arrow : Zoom out");
	mlx_string_put(p->mlx, p->win, 25, 160, 0xffffffff, \
			"W / A / S / D : Translations");
	mlx_string_put(p->mlx, p->win, 25, 180, 0xffffffff, \
			"+ : Increase altitude");
	mlx_string_put(p->mlx, p->win, 25, 200, 0xffffffff, \
			"- : Decrease altitude");
}
