/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 14:40:23 by ratin             #+#    #+#             */
/*   Updated: 2019/09/05 16:54:36 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		parse_error(t_asm *asmbly, int line, char *str)
{
	ft_putstr_fd("bad parsing at line ", 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd(" for ", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	quit_prog(asmbly, 1);
}

void		parse(t_asm *asmbly, char *str, int turn)
{
	if (check_comment(str) == 1)
		return ;
	else if (name_presence(str) == 1 && asmbly->got_name == 0)
		get_name(asmbly, str);
	else if ((comment_presence(str) == 1 && asmbly->got_comment == 0)
		|| asmbly->in_comment == 1)
		get_comment(asmbly, str);
	else if (is_empty(asmbly, str) == 1)
		return ;
	else if (asmbly->got_name == 1 && asmbly->got_comment == 1)
		get_instruction(asmbly, str, turn + 1);
	else
	{
		free(str);
		parse_error(asmbly, turn, str);
	}
}

static int	open_file(t_asm *asmbly, char *str)
{
	int		fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Can't read source file ", 2);
		ft_putstr_fd(str, 2);
		ft_putchar_fd('\n', 2);
		quit_prog(asmbly, 0);
	}
	return (fd);
}

void		check_name(t_asm *asmbly, char *file)
{
	int		i;

	i = 0;
	if (ft_strlen(file) < 2)
	{
		ft_putstr_fd("bad file name\n", 2);
		quit_prog(asmbly, 0);
	}
	while (file[i])
		i++;
	if (file[i - 1] == 's' && file[i - 2] == '.')
		return ;
	else
	{
		ft_putstr_fd("bad file name\n", 2);
		quit_prog(asmbly, 0);
	}
}

int			parse_file(t_asm *asmbly, char *file)
{
	int		fd_file;
	char	*str;
	int		turn;

	str = NULL;
	turn = 0;
	fd_file = open_file(asmbly, file);
	check_name(asmbly, file);
	while (get_next_line(fd_file, &str) > 0)
	{
		parse(asmbly, str, turn);
		if (str != NULL)
			free(str);
		turn++;
	}
	free(str);
	if (asmbly->instru == NULL)
	{
		ft_putstr_fd("No instruction found\n", 2);
		quit_prog(asmbly, 0);
	}
	return (SUCCESS);
}
