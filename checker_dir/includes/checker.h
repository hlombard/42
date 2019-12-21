/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 13:01:10 by hlombard          #+#    #+#             */
/*   Updated: 2019/11/29 15:00:30 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "ft_printf.h"

# define DEBUG	0

typedef struct			s_check
{
	int			*list_a;
	int			*list_b;

	int			size;
	int			size_a;
	int			size_b;
}						t_check;

void					quit_checker(char *str, int type, t_check *check);

int						check_values(char **tab, t_check *check);
int						check_argument(int ac, char **av, t_check *check);
int						check_maxint(char **tab, t_check *check);
int						check_sign(char **tab, int j);
void					verify_arguments(int ac, char **av, t_check *check);
void					stock_numbers(int ac, char **av, t_check *check);
int						check_doubles(t_check *check);

void					invert_stack(t_check *check);
void					read_ops(t_check *check);

void					swap(t_check *check, char **line);
void					push(t_check *check, char **line);
void					rotate(t_check *check, char **line);
void					rev_rotate(t_check *check, char **line);

void					print_stack(t_check *check);

void					judge(t_check *check);

void					swap_a(t_check *check, int verbose);
void					swap_b(t_check *check, int verbose);
void					swap_both(t_check *check, int verbose);
void					push_a(t_check *check, int verbose);
void					push_b(t_check *check, int verbose);

void					rotate_a(t_check *check, int verbose);
void					rotate_b(t_check *check, int verbose);
void					rotate_both(t_check *check, int verbose);
void					rev_rotate_a(t_check *check, int verbose);
void					rev_rotate_b(t_check *check, int verbose);
void					rev_rotate_both(t_check *check, int verbose);

#endif
