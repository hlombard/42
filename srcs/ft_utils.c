/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 21:35:54 by hlombard          #+#    #+#             */
/*   Updated: 2019/04/01 12:56:56 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_free_map(t_fdf *p)
{
	int i;

	i = 0;
	while (i < p->file_y)
	{
		free(p->map[i]);
		i++;
	}
	free(p->map);
}

void	ft_x_bigger_than_y(int y, int x, int xinc, t_fdf *p)
{
	int i;

	i = 1;
	p->cumul = p->dx / 2;
	while (i++ <= p->dx)
	{
		x += xinc;
		p->cumul += p->dy;
		if (p->cumul >= p->dx)
		{
			p->cumul -= p->dx;
			y += p->yinc;
		}
		ft_insert_color(y, x, p);
	}
}

void	ft_x_less_than_y(int y, int x, int xinc, t_fdf *p)
{
	int i;

	i = 1;
	p->cumul = p->dy / 2;
	while (i++ <= p->dy)
	{
		y += p->yinc;
		p->cumul += p->dx;
		if (p->cumul >= p->dy)
		{
			p->cumul -= p->dy;
			x += xinc;
		}
		ft_insert_color(y, x, p);
	}
}

int		ft_exit_hook(t_fdf *param)
{
	mlx_clear_window(param->mlx, param->win);
	mlx_destroy_window(param->mlx, param->win);
	ft_printf("{red}{bold}Window closed with X button\n");
	exit(0);
}

int		ft_usage(void)
{
	ft_printf("\n{green}{bold}Usage:\n\n{eoc}");
	ft_printf("{green}Mandatory{eoc}\n");
	ft_printf("{magenta}Optional{eoc}\n\n");
	ft_printf("{green}{bold}./fdf{eoc} {green}[map]{eoc} ");
	ft_printf("{magenta}[Window width]");
	ft_printf(" [Window height]{eoc}\n");
	return (0);
}
