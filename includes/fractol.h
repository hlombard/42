/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 16:24:06 by hlombard          #+#    #+#             */
/*   Updated: 2019/07/23 12:50:47 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/libft.h"
# include "../libft/includes/ft_printf.h"
# include "mlx.h"
# include <OpenCL/opencl.h>
# include <sys/stat.h>

# define ESCAPE_KEY			0x35
# define SPACE_KEY			49
# define ZOOM_IN			4
# define ZOOM_OUT			5

# define KEY_PAD_1          83
# define KEY_PAD_2          84
# define KEY_PAD_3          85
# define KEY_PAD_4          86
# define KEY_PAD_5          87
# define KEY_PAD_6          88
# define KEY_PAD_7          89
# define KEY_PAD_8          91
# define KEY_PAD_9			92

# define KEY_MINUS        	78
# define KEY_PLUS			69

# define KEY_W              13
# define KEY_A              0
# define KEY_S              1
# define KEY_D              2

# define KEY_C              8
# define KEY_M              46

# define DEFAULT		265
# define BLACK 			0x000000
# define WHITE			16777215
# define YELLOW 		640
# define ORANGE 		15890507
# define RED 			15869459
# define GREEN 			1817755
# define LIGHT_BLUE 	1684990
# define DARK_BLUE 		4484275
# define PURPLE 		6697881

typedef	struct			s_kernel
{
	char				*file_content;

	struct stat			stat_ret;
	size_t				local;
	size_t				st_size;
	size_t				global_item_size;

	cl_platform_id		platform_id;
	cl_device_id		device_id;
	cl_uint				ret_num_devices;
	cl_uint				ret_num_platforms;
	cl_int				ret;
	cl_context			context;
	cl_command_queue	command_queue;
	cl_program			program;
	cl_kernel			kernel;

	cl_mem				results;
	cl_mem				input;

}						t_kernel;

typedef	struct			s_fract
{
	void			*mlx;
	void			*win;
	void			*data_addr;
	int				*data_buffer;

	int				width;
	int				height;
	int				type;
	int				color;
	int				max_ite;

	double			real;
	double			imag;
	double			newreal;
	double			newimag;
	double			oldreal;
	double			oldimag;
	double			zoom;
	double			move_x;
	double			move_y;

	int				menu_type;
	int				julia_motion;

	struct s_kernel	kernel;

}						t_fract;

void					set_window_size(t_fract *fract, char **av, int ac);
void					which_type_and_init(t_fract *fract, char **av);
void					show_usage(void);
void					fractol_exit(char *str);
void					init_sdl(t_fract *fract);

void					init_mandelbrot(t_fract *fract);
void					init_julia(t_fract *fract);
void					init_bs(t_fract *fract);
void					init_tricorn(t_fract *fract);

void					get_file_info(t_kernel *kernel, int fd, int type);
void					draw_with_gpu(t_kernel *kernel, t_fract *fract);
void					set_input(double *double_input, t_fract *fract);
void					read_kernel(t_kernel *kernel, int type);
void					init_opencl(t_fract *fract, t_kernel *kernel);
void					create_kernel(t_fract *fract, t_kernel *kernel);
void					exec_kernel(t_kernel *kernel, t_fract *fract);

int						key_hook(int keycode, t_fract *fract);
void					switch_color_and_redraw(int keycode, t_fract *fract);
int						zoom(int mouse_keycode, int x, int y, t_fract *fract);
void					julia_motion_on_off(t_fract *fract);
void					set_translations(int keycode, t_fract *fract);
void					adjust_ite(int keycode, t_fract *fract);
int						julia_motion(int x, int y, t_fract *fract);
int						exit_hook(t_fract *fract);
void					loop_and_check_events(t_fract *fract);
void					key_hook_2(int keycode, t_fract *fract);
void					add_menu(t_fract *fract);
void					menu_type_2(t_fract *fract);

#endif
