/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 18:26:59 by hlombard          #+#    #+#             */
/*   Updated: 2019/04/01 13:13:45 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_p_projection(t_fdf *p)
{
	mlx_clear_window(p->mlx, p->win);
	ft_clear_image(p);
	p->type = 1;
	p->alt = 0;
	p->pxl_gap = 40;
	ft_pxl_gap(p);
	p->trans_x = 0;
	p->trans_y = 0;
	ft_draw_fdf(p);
	mlx_put_image_to_window(p->mlx, p->win, p->data_addr, 0, 0);
	ft_add_menu(p);
}

void	ft_i_projection(t_fdf *p)
{
	mlx_clear_window(p->mlx, p->win);
	ft_clear_image(p);
	p->type = 0;
	p->alt = 0;
	p->pxl_gap = 40;
	ft_pxl_gap(p);
	p->trans_x = 0;
	p->trans_y = 0;
	ft_draw_fdf(p);
	mlx_put_image_to_window(p->mlx, p->win, p->data_addr, 0, 0);
	ft_add_menu(p);
}

void	ft_increase_alt(t_fdf *p)
{
	mlx_clear_window(p->mlx, p->win);
	ft_clear_image(p);
	p->alt += 1;
	ft_draw_fdf(p);
	mlx_put_image_to_window(p->mlx, p->win, p->data_addr, 0, 0);
	ft_add_menu(p);
}

void	ft_decrease_alt(t_fdf *p)
{
	mlx_clear_window(p->mlx, p->win);
	ft_clear_image(p);
	p->alt -= 1;
	ft_draw_fdf(p);
	mlx_put_image_to_window(p->mlx, p->win, p->data_addr, 0, 0);
	ft_add_menu(p);
}

void	ft_clear_image(t_fdf *p)
{
	int i;

	i = 0;
	while (i < p->width * p->height * 4)
		p->data_buffer[i++] = 0;
	p->index_i = 0;
	p->index_j = 0;
}
