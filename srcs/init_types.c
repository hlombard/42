/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_types.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 17:15:01 by hlombard          #+#    #+#             */
/*   Updated: 2019/07/22 20:11:35 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	init_mandelbrot(t_fract *fract)
{
	fract->julia_motion = 0;
	fract->max_ite = 300;
	fract->zoom = 0.60;
	fract->move_x = -0.5;
	fract->move_y = 0;
	fract->color = DEFAULT;
	fract->menu_type = 0;
	fract->width = 1920;
	fract->height = 1080;
}

void	init_julia(t_fract *fract)
{
	fract->julia_motion = 1;
	fract->max_ite = 100;
	fract->zoom = 0.60;
	fract->move_x = 0;
	fract->move_y = 0;
	fract->real = 0.7;
	fract->imag = 0.27015;
	fract->color = DEFAULT;
	fract->menu_type = 0;
	fract->width = 1920;
	fract->height = 1080;
}

void	init_bs(t_fract *fract)
{
	fract->julia_motion = 0;
	fract->max_ite = 100;
	fract->zoom = 0.90;
	fract->move_x = -0.5;
	fract->move_y = -0.5;
	fract->color = DEFAULT;
	fract->menu_type = 0;
	fract->width = 1920;
	fract->height = 1080;
}

void	init_tricorn(t_fract *fract)
{
	fract->julia_motion = 0;
	fract->max_ite = 300;
	fract->zoom = 0.50;
	fract->move_x = 0.01;
	fract->move_y = 0;
	fract->color = DEFAULT;
	fract->menu_type = 0;
	fract->width = 1920;
	fract->height = 1080;
}
