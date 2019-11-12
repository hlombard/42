/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 13:16:02 by hlombard          #+#    #+#             */
/*   Updated: 2019/10/29 11:36:34 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <fcntl.h>
# include <limits.h>
# include "ft_printf.h"
# include "mlx.h"

# if __APPLE__
#  define W_KEY			0xD
#  define S_KEY			0x1
#  define A_KEY			0x0
#  define D_KEY			0x2
#  define PLUS_KEY		0x45
#  define MINUS_KEY		0x4E
#  define ESCAPE_KEY	0x35

#  define P_KEY			0x23
#  define I_KEY			0x22

#  define UP_ARROW		0x7E
#  define DOWN_ARROW	0x7D

#  define C_KEY			0x8

# elif __linux__
#  define W_KEY			0x0077
#  define S_KEY			0x0073
#  define A_KEY			0x0061
#  define D_KEY			0x0064
#  define PLUS_KEY		0xffab
#  define MINUS_KEY		0xffad
#  define ESCAPE_KEY	0xff1b

#  define P_KEY			0x0070
#  define I_KEY			0x0069

#  define UP_ARROW		0xff52
#  define DOWN_ARROW	0xff54

#  define C_KEY			0x0063

# endif

typedef struct			s_fdf
{
	int		width;
	int		height;

	int		**map;
	int		file_y;
	int		file_xmax;

	float	coef1;
	float	coef2;

	void	*mlx;
	void	*win;
	void	*data_addr;

	char	*data_buffer;

	int		dx;
	int		dy;

	int		x0;
	int		y0;
	int		z0;
	int		color_0;

	int		x1;
	int		y1;
	int		z1;
	int		color_1;

	int		pxl_gap;
	int		alt;
	int		trans_x;
	int		trans_y;

	float	angle;

	int		type;

	int		index_i;
	int		index_j;

	int		cumul;

	int		yinc;
}						t_fdf;

typedef struct			s_parse
{
	int		fd;
	int		ac;
	char	**av;
	int		verif;
	int		y;
	char	*line;
	int		x;
	char	**map_x;

}						t_parse;

void					ft_check_window_size(t_parse *f, t_fdf *p);
void					ft_init_f(t_parse *f);
void					ft_init_p(t_fdf *p);

int						ft_get_map(t_parse *f, t_fdf *p);
int						ft_stock_map(t_parse *f, t_fdf *p);
int						ft_size_tab(char **tab);
int						ft_check_file(t_parse *f, t_fdf *p);

void					ft_draw_background(t_fdf *p);
void					ft_fdf(t_fdf *p);
void					ft_insert_color(int y, int x, t_fdf *p);
void					ft_draw_fdf(t_fdf *p);
int						ft_iso_x(t_fdf *p, int y, int x, int z);
int						ft_iso_y(t_fdf *p, int y, int x, int z);
void					ft_pxl_gap(t_fdf *p);

void					ft_draw_line(t_fdf *p);
void					ft_x_bigger_than_y(int y, int x, int xinc, t_fdf *p);
void					ft_x_less_than_y(int y, int x, int xinc, t_fdf *p);
void					ft_draw_h(t_fdf *p, int z, int y, int x);
void					ft_draw_v(t_fdf *p, int y, int x);

int						ft_generic_hooks(int keycode, t_fdf *p);
int						ft_other_hooks(int keycode, t_fdf *p);

void					ft_increase_alt(t_fdf *p);
void					ft_decrease_alt(t_fdf *p);
void					ft_translate_x(t_fdf *p);
void					ft_translate_y(t_fdf *p);
void					ft_clear_image(t_fdf *p);
void					ft_zoom_in(t_fdf *p);
void					ft_zoom_out(t_fdf *p);
void					ft_p_projection(t_fdf *p);
void					ft_i_projection(t_fdf *p);
void					ft_clear_window(t_fdf *p);

double					ft_percent(int start, int end, int current);
int						ft_get_light(int start, int end, double percentage);
int						ft_get_color(t_fdf *p, int x, int y);
void					ft_point_color(int *color, int z);
void					ft_add_menu(t_fdf *p);

int						ft_usage(void);
int						ft_exit_hook(t_fdf *param);
void					ft_free_map(t_fdf *p);

#endif
