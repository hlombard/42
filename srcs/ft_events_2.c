/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:01:18 by hlombard          #+#    #+#             */
/*   Updated: 2019/04/01 12:45:45 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_translate_x(t_fdf *p)
{
	mlx_clear_window(p->mlx, p->win);
	ft_clear_image(p);
	ft_draw_fdf(p);
	mlx_put_image_to_window(p->mlx, p->win, p->data_addr, 0, 0);
	ft_add_menu(p);
}

void	ft_translate_y(t_fdf *p)
{
	mlx_clear_window(p->mlx, p->win);
	ft_clear_image(p);
	ft_draw_fdf(p);
	mlx_put_image_to_window(p->mlx, p->win, p->data_addr, 0, 0);
	ft_add_menu(p);
}

void	ft_zoom_in(t_fdf *p)
{
	mlx_clear_window(p->mlx, p->win);
	ft_clear_image(p);
	p->pxl_gap += 1;
	ft_draw_fdf(p);
	mlx_put_image_to_window(p->mlx, p->win, p->data_addr, 0, 0);
	ft_add_menu(p);
}

void	ft_zoom_out(t_fdf *p)
{
	mlx_clear_window(p->mlx, p->win);
	ft_clear_image(p);
	if (p->pxl_gap - 1 >= 0)
		p->pxl_gap -= 1;
	ft_draw_fdf(p);
	mlx_put_image_to_window(p->mlx, p->win, p->data_addr, 0, 0);
	ft_add_menu(p);
}

void	ft_clear_window(t_fdf *p)
{
	mlx_clear_window(p->mlx, p->win);
	ft_clear_image(p);
	ft_add_menu(p);
}
