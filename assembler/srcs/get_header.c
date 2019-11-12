/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 15:42:13 by ratin             #+#    #+#             */
/*   Updated: 2019/09/05 16:53:48 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	error_length(t_asm *asmbly, int selector, char *str)
{
	ft_putstr_fd("Error program ", 2);
	if (selector == 1)
		ft_putstr_fd("name", 2);
	else if (selector == 2)
		ft_putstr_fd("comment", 2);
	ft_putstr_fd(" is too big\n", 2);
	free(str);
	quit_prog(asmbly, 1);
}

void	get_name(t_asm *asmbly, char *str)
{
	size_t	i;
	size_t	y;

	i = 0;
	y = 0;
	while (str[i] && str[i] != '"')
		i++;
	i++;
	if (!(str[i]))
		print_error(asmbly, str);
	while (str[i + y] && str[i + y] != '"')
		y++;
	if (!(str[i + y]))
		print_error(asmbly, str);
	if (!(asmbly->name = ft_strsub(str, i, y)))
	{
		free(str);
		quit_prog(asmbly, 0);
	}
	if (ft_strlen(asmbly->name) > PROG_NAME_LENGTH)
		error_length(asmbly, 1, str);
	asmbly->got_name = 1;
}

int		fill_comment(char *str, t_asm *asmbly, int indexer)
{
	int	i;
	int	idx_lenght;

	i = 0;
	idx_lenght = 0;
	while (str[indexer + i] && str[indexer + i] != '"')
	{
		if (asmbly->idx_comment >= COMMENT_LENGTH)
		{
			idx_lenght = -1;
			break ;
		}
		asmbly->comment[asmbly->idx_comment] = str[indexer + i];
		asmbly->idx_comment++;
		i++;
	}
	if (idx_lenght == -1)
		error_length(asmbly, 2, str);
	if (str[indexer + i] == '"')
	{
		asmbly->comment[asmbly->idx_comment] = '\0';
		return (0);
	}
	return (1);
}

void	get_next_comment(t_asm *asmbly, char *str, int i)
{
	if (!(fill_comment(str, asmbly, i)))
	{
		asmbly->in_comment = 0;
		asmbly->got_comment = 1;
		return ;
	}
	if (asmbly->idx_comment >= COMMENT_LENGTH)
		error_length(asmbly, 2, str);
	asmbly->comment[asmbly->idx_comment] = '\n';
	asmbly->idx_comment++;
}

void	get_comment(t_asm *asmbly, char *str)
{
	int		i;

	i = 0;
	if (asmbly->in_comment == 0)
	{
		while (str[i] && str[i] != '"')
			i++;
		i++;
		asmbly->in_comment = 1;
		if (!(str[i]))
		{
			if (asmbly->idx_comment >= COMMENT_LENGTH)
				error_length(asmbly, 2, str);
			asmbly->comment[asmbly->idx_comment] = '\n';
			asmbly->idx_comment++;
			return ;
		}
	}
	get_next_comment(asmbly, str, i);
}
