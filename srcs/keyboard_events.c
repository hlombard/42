/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 21:07:27 by hlombard          #+#    #+#             */
/*   Updated: 2019/07/22 20:12:54 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int		key_hook(int keycode, t_fract *fract)
{
	if (keycode == ESCAPE_KEY)
	{
		mlx_clear_window(fract->mlx, fract->win);
		mlx_destroy_window(fract->mlx, fract->win);
		exit(EXIT_SUCCESS);
	}
	if (keycode == SPACE_KEY && fract->type == 2)
		julia_motion_on_off(fract);
	if (keycode == KEY_MINUS || keycode == KEY_PLUS)
		adjust_ite(keycode, fract);
	if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S
			|| keycode == KEY_D)
		set_translations(keycode, fract);
	if (keycode == KEY_M)
	{
		if (keycode == KEY_M && fract->menu_type == 0)
			fract->menu_type = 1;
		else if (keycode == KEY_M && fract->menu_type == 1)
			fract->menu_type = 0;
		draw_with_gpu(&fract->kernel, fract);
	}
	key_hook_2(keycode, fract);
	return (0);
}

void	key_hook_2(int keycode, t_fract *fract)
{
	if (keycode == KEY_PAD_1 || keycode == KEY_PAD_2 || keycode == KEY_PAD_3
			|| keycode == KEY_PAD_4 || keycode == KEY_PAD_5
			|| keycode == KEY_PAD_6 || keycode == KEY_PAD_7
			|| keycode == KEY_PAD_8 || keycode == KEY_PAD_9)
		switch_color_and_redraw(keycode, fract);
	if (keycode == KEY_C)
	{
		fract->type == 1 ? init_mandelbrot(fract) : 0;
		fract->type == 2 ? init_julia(fract) : 0;
		fract->type == 3 ? init_bs(fract) : 0;
		fract->type == 4 ? init_tricorn(fract) : 0;
		draw_with_gpu(&fract->kernel, fract);
	}
}

void	adjust_ite(int keycode, t_fract *fract)
{
	if (keycode == KEY_PLUS)
	{
		fract->max_ite += 10;
		draw_with_gpu(&fract->kernel, fract);
	}
	else if (keycode == KEY_MINUS)
	{
		fract->max_ite -= 10;
		draw_with_gpu(&fract->kernel, fract);
	}
}

void	set_translations(int keycode, t_fract *fract)
{
	if (keycode == KEY_W)
		fract->move_y -= 0.05 / (fract->zoom * 2);
	else if (keycode == KEY_A)
		fract->move_x -= 0.05 / (fract->zoom * 2);
	else if (keycode == KEY_S)
		fract->move_y += 0.05 / (fract->zoom * 2);
	else
		fract->move_x += 0.05 / (fract->zoom * 2);
	draw_with_gpu(&fract->kernel, fract);
}

void	switch_color_and_redraw(int keycode, t_fract *fract)
{
	if (keycode == KEY_PAD_1)
		fract->color = DEFAULT;
	else if (keycode == KEY_PAD_2)
		fract->color = WHITE;
	else if (keycode == KEY_PAD_3)
		fract->color = YELLOW;
	else if (keycode == KEY_PAD_4)
		fract->color = ORANGE;
	else if (keycode == KEY_PAD_5)
		fract->color = RED;
	else if (keycode == KEY_PAD_6)
		fract->color = GREEN;
	else if (keycode == KEY_PAD_7)
		fract->color = LIGHT_BLUE;
	else if (keycode == KEY_PAD_8)
		fract->color = DARK_BLUE;
	else if (keycode == KEY_PAD_9)
		fract->color = PURPLE;
	draw_with_gpu(&fract->kernel, fract);
}
