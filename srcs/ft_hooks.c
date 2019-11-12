/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 18:36:45 by hlombard          #+#    #+#             */
/*   Updated: 2019/04/01 13:23:52 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		ft_generic_hooks(int keycode, t_fdf *p)
{
	if (keycode == ESCAPE_KEY)
	{
		mlx_clear_window(p->mlx, p->win);
		mlx_destroy_window(p->mlx, p->win);
		ft_free_map(p);
		exit(0);
	}
	if (keycode == P_KEY)
		ft_p_projection(p);
	if (keycode == I_KEY)
		ft_i_projection(p);
	if (keycode == PLUS_KEY)
		ft_increase_alt(p);
	if (keycode == MINUS_KEY)
		ft_decrease_alt(p);
	if (keycode == UP_ARROW)
		ft_zoom_in(p);
	if (keycode == DOWN_ARROW)
		ft_zoom_out(p);
	if (keycode == W_KEY || keycode == S_KEY ||
			keycode == A_KEY || keycode == D_KEY ||
			keycode == C_KEY)
		return (ft_other_hooks(keycode, p));
	return (0);
}

int		ft_other_hooks(int keycode, t_fdf *p)
{
	if (keycode == W_KEY)
	{
		p->trans_y -= 5;
		ft_translate_y(p);
	}
	if (keycode == S_KEY)
	{
		p->trans_y += 5;
		ft_translate_y(p);
	}
	if (keycode == A_KEY)
	{
		p->trans_x -= 5;
		ft_translate_x(p);
	}
	if (keycode == D_KEY)
	{
		p->trans_x += 5;
		ft_translate_x(p);
	}
	if (keycode == C_KEY)
		ft_clear_window(p);
	return (0);
}
