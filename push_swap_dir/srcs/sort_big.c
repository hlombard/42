/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:15:01 by hlombard          #+#    #+#             */
/*   Updated: 2019/11/29 14:48:43 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_big(t_check *check, int nb_chunks)
{
	int	**chunks;

	chunks = create_chunks(check, nb_chunks, 0, -1);
	if (chunks == NULL)
		return ;
	all_to_stack_b(chunks, check, nb_chunks);
	all_to_stack_a(check);
	free_chunks(chunks, nb_chunks);
}

int		opti_possible(t_check *check, int index_1, int index_2)
{
	if (index_2 != index_1 && index_2 < index_1 + 1 && check->size_b)
	{
		if (element_id(right_place_b(check->list_a[index_2], check), 2,
				check) < check->size_b / 2)
		{
			best_setup(check, index_2);
			if (check->list_b[check->size_b - 1] !=
					right_place_b(check->list_a[check->size_a - 1], check))
			{
				while (check->list_b[check->size_b - 1] !=
						right_place_b(check->list_a[check->size_a - 1], check))
				{
					if (element_id(right_place_b(check->list_a[check->size_a \
									- 1], check), 2, check) < check->size_b / 2)
						rev_rotate_b(check, 1);
					else
						rotate_b(check, 1);
				}
			}
			push_b(check, 1);
			return (1);
		}
	}
	return (0);
}

void	all_to_stack_b(int **chunks, t_check *check, int nb_chunks)
{
	int	i;
	int	index_1;
	int	index_2;

	i = -1;
	while (check->size_a != 0)
	{
		while (++i < nb_chunks)
		{
			while (still_exists_current_chunk(chunks[i], check))
			{
				index_1 = scan_from_top(chunks[i], check);
				index_2 = scan_from_bot(chunks[i], check);
				if (opti_possible(check, index_1, index_2))
					continue;
				if (index_2 != index_1 && index_2 < index_1 + 1)
					move_nb(index_2, 1, check);
				else
					move_nb(index_1, 2, check);
			}
		}
	}
}

void	push_to_b_when_ok(int nb, t_check *check)
{
	if (check->size_b < 2)
	{
		push_b(check, 1);
		return ;
	}
	while (check->list_b[check->size_b - 1] != right_place_b(nb, check))
	{
		if (element_id(right_place_b(nb, check), 2, check) < check->size_b / 2)
			rev_rotate_b(check, 1);
		else
			rotate_b(check, 1);
	}
	push_b(check, 1);
}

void	all_to_stack_a(t_check *check)
{
	while (check->size_b)
	{
		while (check->list_b[check->size_b - 1] != biggest(2, check))
		{
			if (element_id(biggest(2, check), 2, check) > check->size_b / 2)
				rotate_b(check, 1);
			else
				rev_rotate_b(check, 1);
		}
		push_a(check, 1);
	}
}
