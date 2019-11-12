/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 17:58:03 by hlombard          #+#    #+#             */
/*   Updated: 2019/04/01 13:14:04 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_draw_line(t_fdf *p)
{
	int x;
	int y;
	int xinc;

	x = p->x0;
	y = p->y0;
	p->dx = p->x1 - p->x0;
	p->dy = p->y1 - p->y0;
	xinc = (p->dx > 0) ? 1 : -1;
	p->yinc = (p->dy > 0) ? 1 : -1;
	p->dx = abs(p->dx);
	p->dy = abs(p->dy);
	ft_insert_color(y, x, p);
	if (p->dx > p->dy)
		ft_x_bigger_than_y(y, x, xinc, p);
	else
		ft_x_less_than_y(y, x, xinc, p);
}

void	ft_draw_fdf(t_fdf *p)
{
	int y;
	int x;
	int z;

	y = 0;
	while (y < p->file_y)
	{
		x = 0;
		while (x < p->file_xmax)
		{
			z = p->map[y][x];
			if (p->map[y][x] != 0)
				z += p->alt;
			ft_draw_h(p, z, y, x);
			ft_draw_v(p, y, x);
			p->index_i++;
			x++;
		}
		p->index_i = 0;
		p->index_j++;
		y++;
	}
}

void	ft_draw_h(t_fdf *p, int z, int y, int x)
{
	p->x0 = ft_iso_x(p, y, x, z);
	p->y0 = ft_iso_y(p, y, x, z);
	if (p->index_i >= p->file_xmax - 1)
		return ;
	p->z0 = p->map[y][x];
	if (p->z0 != 0)
		p->z0 += p->alt;
	p->z1 = p->map[y][x + 1];
	if (p->z1 != 0)
		p->z1 += p->alt;
	p->x1 = ft_iso_x(p, y, x + 1, p->z1);
	p->y1 = ft_iso_y(p, y, x + 1, p->z1);
	ft_draw_line(p);
}

void	ft_draw_v(t_fdf *p, int y, int x)
{
	if (p->index_j >= p->file_y - 1)
		return ;
	p->z0 = p->map[y][x];
	if (p->z0 != 0)
		p->z0 += p->alt;
	p->z1 = p->map[y + 1][x];
	if (p->z1 != 0)
		p->z1 += p->alt;
	p->x1 = ft_iso_x(p, y + 1, x, p->z1);
	p->y1 = ft_iso_y(p, y + 1, x, p->z1);
	ft_draw_line(p);
}

void	ft_insert_color(int y, int x, t_fdf *p)
{
	int i;
	int j;
	int color;
	int color_n;

	j = 0;
	i = (x + y * p->width) * 4;
	ft_point_color(&p->color_0, p->z0);
	ft_point_color(&p->color_1, p->z1);
	color = ft_get_color(p, x, y);
	while (j < 4)
	{
		color_n = (color >> (8 * j)) & 0xff;
		if ((y < p->height && y > 0) && (x < p->width && x > 0))
			p->data_buffer[i] = color_n;
		j++;
		i++;
	}
}
