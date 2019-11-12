/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 21:22:53 by hlombard          #+#    #+#             */
/*   Updated: 2019/07/22 20:08:56 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int		julia_motion(int x, int y, t_fract *fract)
{
	if (fract->type == 2 && fract->julia_motion == 1)
	{
		if (x >= 0 && y >= 0 && x <= fract->width && y <= fract->height)
		{
			fract->real = -0.7 + (double)x / fract->width;
			fract->imag = 0.27015 + (double)y / fract->height;
			draw_with_gpu(&fract->kernel, fract);
		}
	}
	return (0);
}

int		zoom(int mouse_keycode, int x, int y, t_fract *fract)
{
	if (mouse_keycode == ZOOM_IN && fract->julia_motion == 0)
	{
		fract->zoom *= 1.1;
		fract->move_y += (y - fract->height / 2) * 0.0002 / fract->zoom;
		fract->move_x += (x - fract->width / 2) * 0.00015 / fract->zoom;
		draw_with_gpu(&fract->kernel, fract);
	}
	else if (mouse_keycode == ZOOM_OUT && fract->julia_motion == 0)
	{
		if (fract->zoom > 0.6)
		{
			fract->zoom /= 1.1;
			fract->move_y += (fract->height / 2 - y) * 0.0002 / fract->zoom;
			fract->move_x += (fract->width / 2 - x) * 0.00015 / fract->zoom;
			draw_with_gpu(&fract->kernel, fract);
		}
	}
	return (0);
}

int		exit_hook(t_fract *fract)
{
	mlx_clear_window(fract->mlx, fract->win);
	mlx_destroy_window(fract->mlx, fract->win);
	exit(-1);
}
