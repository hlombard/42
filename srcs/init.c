/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 16:29:11 by hlombard          #+#    #+#             */
/*   Updated: 2019/07/22 20:05:43 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void		which_type_and_init(t_fract *fract, char **av)
{
	if (!ft_strcmp(av[1], "-mandelbrot"))
	{
		fract->type = 1;
		init_mandelbrot(fract);
	}
	else if (!ft_strcmp(av[1], "-julia"))
	{
		fract->type = 2;
		init_julia(fract);
	}
	else if (!ft_strcmp(av[1], "-bs"))
	{
		fract->type = 3;
		init_bs(fract);
	}
	else if (!ft_strcmp(av[1], "-tricorn"))
	{
		fract->type = 4;
		init_tricorn(fract);
	}
	else
		show_usage();
}

void		init_sdl(t_fract *fract)
{
	int	bpp;
	int	s_l;
	int	end;

	if (!(fract->mlx = mlx_init()))
		fractol_exit("Couldn't init mlx");
	if (!(fract->win = mlx_new_window(fract->mlx, fract->width,
				fract->height, "Fractol")))
		fractol_exit("Couldn't create window");
	if (!(fract->data_addr = mlx_new_image(fract->mlx, fract->width,
				fract->height)))
		fractol_exit("Couldn't create image");
	if (!(fract->data_buffer = (int*)mlx_get_data_addr(fract->data_addr,
				&bpp, &s_l, &end)))
		fractol_exit("Couldn't get image data buffer");
}
