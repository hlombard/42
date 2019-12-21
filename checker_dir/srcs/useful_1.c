/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 17:49:28 by hlombard          #+#    #+#             */
/*   Updated: 2019/12/09 18:26:27 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	read_ops(t_check *check)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line, 0, 0) > 0)
	{
		if (!ft_strcmp(line, "sa") || !ft_strcmp(line, "sb")
				|| !ft_strcmp(line, "ss"))
			swap(check, &line);
		else if (!ft_strcmp(line, "pa") || !ft_strcmp(line, "pb"))
			push(check, &line);
		else if (!ft_strcmp(line, "ra") || !ft_strcmp(line, "rb")
				|| !ft_strcmp(line, "rr"))
			rotate(check, &line);
		else if (!ft_strcmp(line, "rra") || !ft_strcmp(line, "rrb")
				|| !ft_strcmp(line, "rrr"))
			rev_rotate(check, &line);
		else
		{
			free(line);
			quit_checker("Error", 2, check);
		}
	}
}

void	swap(t_check *check, char **line)
{
	if (!ft_strcmp(*line, "sa"))
	{
		free(*line);
		swap_a(check, 0);
	}
	else if (!ft_strcmp(*line, "sb"))
	{
		free(*line);
		swap_b(check, 0);
	}
	else
	{
		free(*line);
		swap_both(check, 0);
	}
}

void	push(t_check *check, char **line)
{
	if (!ft_strcmp(*line, "pa"))
	{
		free(*line);
		push_a(check, 0);
	}
	else
	{
		free(*line);
		push_b(check, 0);
	}
}

void	rotate(t_check *check, char **line)
{
	if (!ft_strcmp(*line, "ra"))
	{
		free(*line);
		rotate_a(check, 0);
	}
	else if (!ft_strcmp(*line, "rb"))
	{
		free(*line);
		rotate_b(check, 0);
	}
	else
	{
		free(*line);
		rotate_both(check, 0);
	}
}

void	rev_rotate(t_check *check, char **line)
{
	if (!ft_strcmp(*line, "rra"))
	{
		free(*line);
		rev_rotate_a(check, 0);
	}
	else if (!ft_strcmp(*line, "rrb"))
	{
		free(*line);
		rev_rotate_b(check, 0);
	}
	else
	{
		free(*line);
		rev_rotate_both(check, 0);
	}
}
