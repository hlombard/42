/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 16:23:26 by hlombard          #+#    #+#             */
/*   Updated: 2019/07/22 20:10:05 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	show_usage(void)
{
	ft_printf("\n\tUsage: ./fractol {green}Fractal\n\n{eoc}");
	ft_printf("{green}=> Fractal:{eoc}\n\n");
	ft_printf("Fractal, has to be:\n\n");
	ft_printf("\t\t   -mandelbrot\n");
	ft_printf("\t\t   -julia\n");
	ft_printf("\t\t   -bs\n");
	ft_printf("\t\t   -tricorn\n");
	exit(-1);
}

void	loop_and_check_events(t_fract *fract)
{
	mlx_key_hook(fract->win, key_hook, fract);
	mlx_hook(fract->win, 6, 1L < 6, julia_motion, fract);
	mlx_hook(fract->win, 17, 0, exit_hook, fract);
	mlx_mouse_hook(fract->win, zoom, fract);
	mlx_loop(fract->mlx);
}

void	draw_with_gpu(t_kernel *kernel, t_fract *fract)
{
	exec_kernel(kernel, fract);
	mlx_clear_window(fract->mlx, fract->win);
	mlx_put_image_to_window(fract->mlx, fract->win, fract->data_addr, 0, 0);
	add_menu(fract);
}

int		main(int ac, char **av)
{
	t_fract		fract;

	if (ac == 2)
	{
		which_type_and_init(&fract, av);
		read_kernel(&fract.kernel, fract.type);
		init_sdl(&fract);
		init_opencl(&fract, &fract.kernel);
		draw_with_gpu(&fract.kernel, &fract);
		loop_and_check_events(&fract);
		return (0);
	}
	else
		show_usage();
}
