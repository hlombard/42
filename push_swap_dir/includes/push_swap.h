/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:21:55 by hlombard          #+#    #+#             */
/*   Updated: 2019/11/29 16:01:45 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

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

void					solve(t_check *check);

void					verify_arguments(int ac, char **av, t_check *check);
int						check_argument(int ac, char **av, t_check *check);
int						check_values(char **tab, t_check *check);
int						check_sign(char **tab, int j);
int						check_maxint(char **tab, t_check *check);

void					sort_3_numbers(t_check *check);
void					sort_first_stack(t_check *check);
void					sort_4_5_numbers(t_check *check);

void					quit_ps(char *str, int type, t_check *check);
void					invert_stack(t_check *check);
int						is_sorted(t_check *check);
int						biggest(int stack, t_check *check);
int						smallest(int stack, t_check *check);

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

int						**create_chunks(t_check *check, int nb_chunks,
						int i, int j);
int						still_exists_current_chunk(int *chunk,
						t_check *check);
void					free_chunks(int **chunks, int nb_chunks);

int						right_place_a(int nb, t_check *check);
int						right_place_b(int nb, t_check *check);
int						scan_from_top(int *chunk, t_check *check);
int						scan_from_bot(int *chunk, t_check *check);
int						element_id(int nb, int stack, t_check *check);

void					sort_big(t_check *check, int nb_chunks);
int						opti_possible(t_check *check, int index_1, int index_2);
void					all_to_stack_b(int **chunks, t_check *check,
						int nb_chunks);
void					push_to_b_when_ok(int nb, t_check *check);
void					all_to_stack_a(t_check *check);

void					print_stack(t_check *check);
void					stock_numbers(int ac, char **av, t_check *check);
int						check_doubles(t_check *check);
void					best_setup(t_check *check, int index_2);
void					move_nb(int index, int type, t_check *check);

#endif
