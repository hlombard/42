/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 21:28:29 by hlombard          #+#    #+#             */
/*   Updated: 2019/04/01 13:23:54 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_init_f(t_parse *f)
{
	f->verif = -1;
	f->y = 0;
	f->line = NULL;
	f->x = 0;
}

void	ft_init_p(t_fdf *p)
{
	p->type = 0;
	p->trans_y = 0;
	p->trans_x = 0;
	p->alt = 0;
	p->index_i = 0;
	p->index_j = 0;
	p->coef1 = 0.7;
	p->coef2 = 0.5;
	p->pxl_gap = 40;
	p->cumul = 0;
	p->yinc = 0;
}

void	ft_check_window_size(t_parse *f, t_fdf *p)
{
	p->width = ft_atoi(f->av[2]);
	p->height = ft_atoi(f->av[3]);
	if (p->width < 640 || p->width > 1920)
	{
		ft_printf("{cyan}Default width set : 1920{eoc}\n");
		p->width = 1920;
	}
	if (p->height < 480 || p->height > 1080)
	{
		ft_printf("{cyan}Default height set : 1080{eoc}\n");
		p->height = 1080;
	}
}

int		main(int ac, char **av)
{
	t_fdf	p;
	t_parse f;

	f.ac = ac;
	f.av = av;
	ft_init_p(&p);
	ft_init_f(&f);
	if (ft_get_map(&f, &p) == 0)
		exit(0);
	ft_fdf(&p);
	return (0);
}
