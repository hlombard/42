/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 21:05:21 by hlombard          #+#    #+#             */
/*   Updated: 2019/04/01 12:44:35 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void		ft_fdf(t_fdf *p)
{
	int bpp;
	int	s_l;
	int	end;

	p->mlx = mlx_init();
	p->win = mlx_new_window(p->mlx, p->width, p->height, "FdF");
	p->data_addr = mlx_new_image(p->mlx, p->width, p->height);
	p->data_buffer = mlx_get_data_addr(p->data_addr,
			&bpp, &s_l, &end);
	ft_pxl_gap(p);
	ft_draw_fdf(p);
	mlx_put_image_to_window(p->mlx, p->win, p->data_addr, 0, 0);
	ft_add_menu(p);
	mlx_do_key_autorepeaton(p->mlx);
	mlx_hook(p->win, 2, (1L << 0), &ft_generic_hooks, p);
	mlx_hook(p->win, 17, (1L << 17), &ft_exit_hook, p);
	mlx_loop(p->mlx);
}

void		ft_pxl_gap(t_fdf *p)
{
	while ((p->file_y * p->pxl_gap) > p->width / 2)
		p->pxl_gap--;
	while ((p->file_xmax * p->pxl_gap) > p->height / 2)
		p->pxl_gap--;
}

int			ft_iso_x(t_fdf *p, int y, int x, int z)
{
	float iso_x;

	if (p->type == 0)
		iso_x = ((p->coef1 * x) - (p->coef2 * y)) * p->pxl_gap;
	else
		iso_x = (x + p->coef1 * -z) * p->pxl_gap;
	return (iso_x + (p->width / 2) + p->trans_x);
}

int			ft_iso_y(t_fdf *p, int y, int x, int z)
{
	float iso_y;

	if (p->type == 0)
		iso_y = (-z + (p->coef1 / 2) * x + (p->coef2 / 2) * y) * p->pxl_gap;
	else
		iso_y = (y + ((p->coef1 / 2) * -z)) * p->pxl_gap;
	return (iso_y + (p->height / 2) + p->trans_y);
}
