/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 00:59:14 by hlombard          #+#    #+#             */
/*   Updated: 2019/09/03 13:42:08 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <inttypes.h>
# include <stdarg.h>
# include "../libft.h"

# define C_NONE         "\033[0m"
# define C_BOLD         "\033[1m"
# define C_RED          "\033[31m"
# define C_GREEN        "\033[32m"
# define C_BLUE         "\033[34m"
# define C_MAGENTA      "\033[35m"
# define C_CYAN         "\033[36m"

typedef struct		s_flags
{
	int		minus;
	int		plus;
	int		hash;
	int		zero;
	int		space;
	int		min_width;
	int		precision;
	int		h;
	int		hh;
	int		l;
	int		ll;
	int		majx;
	int		majl;
	int		j;
	int		z;
	int		zerozero;
}					t_flags;

int					ft_printf(char const *format, ...);
void				ft_init_flags(t_flags *flags);
void				ft_parse_flags(char **str, t_flags *flags);
void				ft_parse_min_width(char **str, t_flags *flags, va_list ap);
void				ft_parse_precision(char **str, t_flags *flags, va_list ap);
void				ft_parse_size(char **str, t_flags *flags);

void				ft_flag_star(t_flags *p, char **str, int size, va_list ap);

int					ft_convert_nbwords(va_list ap);
int					ft_convert_s(t_flags *flags, va_list arg);
int					ft_first_part_s(t_flags *flags,
					char *s, int i, int size);

int					ft_convert_c(t_flags *p, va_list arg);

int					ft_convert_p(t_flags *f, va_list arg);
void				ft_set_prefix_p(t_flags *p, int len, int *added);

int					ft_convert_d_and_i(t_flags *p, va_list arg);
int					ft_show_d_and_i(t_flags *p, int i, int size, intmax_t nb);
void				ft_adjust_flags(t_flags *p, intmax_t nb);

int					ft_convert_o(t_flags *p, va_list ap);
int					ft_show_o(t_flags *p, int i, int size, intmax_t nb);
void				ft_get_right_size_o(t_flags *p, int *size,
					int *oldsize, uintmax_t nb);
int					ft_write_o_and_free(t_flags *p, uintmax_t nb, int i);

int					ft_convert_x_and_majx(t_flags *p, va_list ap);
int					ft_add_prefix(t_flags *p, int i, int *added, uintmax_t nb);
int					ft_add_prefix2(t_flags *p, int i, int added, uintmax_t nb);
void				ft_adjust_size_x(t_flags *p, int *size,
					int *oldsize, uintmax_t nb);
void				ft_initialize_variables(int *a, int *b, int *c, int *d);
int					ft_print_x(t_flags *p, int i, uintmax_t nb);
int					ft_print_maj_x(t_flags *p, int i, uintmax_t nb);
int					ft_print_additional_x(t_flags *p, int size,
					int i, int added);

int					ft_convert_u(t_flags *p, va_list ap);
void				ft_set_size_u(t_flags *p, int *precision,
					int *size, uintmax_t nb);
int					ft_write_u_nb(t_flags *p, int i, uintmax_t nb);
void				ft_get_new_size(t_flags *p, int *size, uintmax_t nb);

int					ft_convert_binary(t_flags *p, va_list ap);
int					ft_get_size(t_flags *p, uintmax_t nb, int *i);
int					ft_write_and_free(t_flags *p, char *str,
					int i, uintmax_t nb);

int					ft_convert_float(t_flags *p, va_list ap);
int					ft_neg_float(t_flags *p, long double *nb, int i, int *sign);
int					ft_check_flags_float(t_flags *p, int *sign,
					int i, long double *nb);
int					ft_threat_float(unsigned long int intpart,
					long double *nb, int i, t_flags *p);
char				*ft_get_my_float(long double nb,
					unsigned long int intpart, t_flags *p);
int					ft_update_size(char *myfloat, t_flags *p,
					unsigned long long int intpart);
int					ft_nb_with_precision(t_flags *p);
int					ft_float_with_minus(char *myfloat, int i,
					int sign, t_flags *p);
int					ft_float_without_minus(char *myfloat, int i,
					int sign, t_flags *p);
int					ft_if_zero_float(int i, int sign,
					char *myfloat, t_flags *p);
int					ft_if_zero_no_minus(t_flags *p, int sign,
					int i, char *myfloat);
int					ft_float_special(t_flags *p, long double nb, int i);
int					ft_if_special_padding(t_flags *p, char *str, int i);

int					ft_convert_percentage(t_flags *p);

int					ft_convert_nb_word(t_flags *p, va_list ap);
void				ft_add_flags_nb_word(t_flags *p, int *j, int size,
					int i);

int					ft_set_colors(char **str);

intmax_t			ft_get_nb_type(t_flags *p, intmax_t nb);
uintmax_t			ft_get_nb_u_type(t_flags *p, uintmax_t nb);

int					ft_print_min_width_no_sign(t_flags *p, int size, int i);
int					ft_print_min_width_no_sign_spe(t_flags *p, int size,
					int i, int added);
int					ft_print_sign(intmax_t nb, t_flags *p, int i);
int					ft_print_min_width(t_flags *p, int size,
					intmax_t nb, int i);
int					ft_print_additional_width(t_flags *p, int size, int i);

char				*ft_itoa_base_spe(intmax_t value, int base, t_flags *p);
char				*ft_itoa_base_spe_cap(intmax_t value, int base,
					t_flags *p);
char				*ft_itoa_sp(uintmax_t value, int base, t_flags *p);
char				*ft_itoa_spc(uintmax_t value, int base, t_flags *p);
char				*ft_itoa_base(int value, int base);
char				*ft_itoa_base_spf(uintmax_t value, int base, t_flags *p);

int					len_base(long long value, int base);

void				ft_get_format(char **str, t_flags *p, va_list ap);
int					ft_write(char **s, t_flags *p, va_list ap);
int					ft_write2(char **s, t_flags *p, va_list ap);
int					ft_write3(char **s, t_flags *p, va_list ap);
int					ft_write4(char **s);

void				ft_putnstr(char *s, int n);
void				ft_putnchar(char c, int n);

int					ft_draw(void);
int					ft_draw2(void);

#endif
