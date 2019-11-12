/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 17:31:19 by hlombard          #+#    #+#             */
/*   Updated: 2019/07/22 20:14:13 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	set_input(double *input, t_fract *fract)
{
	input[0] = fract->zoom;
	input[1] = fract->move_x;
	input[2] = fract->move_y;
	input[3] = fract->max_ite;
	input[6] = fract->color;
	if (fract->type == 2)
	{
		input[4] = fract->real;
		input[5] = fract->imag;
	}
}

void	julia_motion_on_off(t_fract *fract)
{
	if (fract->julia_motion == 1)
	{
		fract->julia_motion = 0;
		ft_printf("Julia motion disabled\n");
		draw_with_gpu(&fract->kernel, fract);
	}
	else
	{
		fract->julia_motion = 1;
		ft_printf("Julia motion enabled\n");
		draw_with_gpu(&fract->kernel, fract);
	}
}

void	add_menu(t_fract *fract)
{
	if (fract->menu_type == 0)
	{
		mlx_string_put(fract->mlx, fract->win, 10, 10,
				0x26EFEC, "Press key 'M' to show options");
	}
	else if (fract->menu_type == 1)
	{
		mlx_string_put(fract->mlx, fract->win, 10, 10,
				0x26EFEC, "End Program: 'ESC'");
		mlx_string_put(fract->mlx, fract->win, 10, 50,
				0x26EFEC, "Translations: W/A/S/D");
		mlx_string_put(fract->mlx, fract->win, 10, 90,
				0x26EFEC, "Colors: KEY PAD '1' to '9'");
		mlx_string_put(fract->mlx, fract->win, 10, 130,
				0x26EFEC, "Increase ITE: KEY PAD '+'");
		mlx_string_put(fract->mlx, fract->win, 10, 170,
				0x26EFEC, "Decrease ITE: KEY PAD '-'");
		mlx_string_put(fract->mlx, fract->win, 10, 210,
				0x26EFEC, "Clear/Reset Fractal: 'C'");
		mlx_string_put(fract->mlx, fract->win, 10, 250,
				0x26EFEC, "Hide MENU: 'M'");
	}
	if (fract->menu_type == 1 && fract->type == 2)
		menu_type_2(fract);
}

void	menu_type_2(t_fract *fract)
{
	mlx_string_put(fract->mlx, fract->win, 10, 290,
			0xFF0000, "Lock Julia Motion: 'SPACE':");
	if (fract->julia_motion == 1)
		mlx_string_put(fract->mlx, fract->win, 290, 290,
				0x008000, "ON");
	else
		mlx_string_put(fract->mlx, fract->win, 290, 290,
				0xFF0000, "OFF");
}

void	fractol_exit(char *str)
{
	ft_printf("%s\n", str);
	exit(-1);
}
