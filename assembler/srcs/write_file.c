/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 02:57:18 by ratin             #+#    #+#             */
/*   Updated: 2019/09/05 16:41:28 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int					atoi_hex(char *str, int fd)
{
	unsigned char	res;
	int				i;
	int				y;

	i = -1;
	y = -1;
	res = 0;
	while (str[++i])
	{
		if (str[i] == ';')
			continue ;
		res = ((res >> 4) | (res << 4));
		if (str[i] >= 48 && str[i] <= 57)
			res = res + (str[i] - 48);
		if (str[i] >= 97 && str[i] <= 102)
			res = res + (str[i] - 87);
		if (y % 2 == 0)
		{
			write(fd, &res, sizeof(unsigned char));
			res = 0;
		}
		y++;
	}
	return (0);
}

void				write_bytecode(t_asm *asmbly, int fd)
{
	t_instru		*instru;
	t_header		*header;

	instru = asmbly->instru;
	header = ft_memalloc(sizeof(t_header));
	header->magic = swap_endian(COREWAR_EXEC_MAGIC);
	header->prog_size = swap_endian(asmbly->size);
	ft_strcpy(header->prog_name, asmbly->name);
	ft_strcpy(header->comment, asmbly->comment);
	write(fd, header, sizeof(t_header));
	while (instru)
	{
		if (instru->conv_par != NULL)
			atoi_hex(instru->conv_par, fd);
		instru = instru->next;
	}
	free(header);
}

void				write_file(t_asm *asmbly, char *file)
{
	int				fd;
	char			*new_file;

	new_file = ft_strndup(file, ft_strlen(file) - 2);
	new_file = ft_strjoin_free(new_file, ".cor", 1);
	fd = open(new_file, O_WRONLY | O_APPEND | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("error when creating the file\n", 2);
		quit_prog(asmbly, 0);
	}
	free(new_file);
	write_bytecode(asmbly, fd);
	if (close(fd) < 0)
	{
		ft_putstr_fd("close error\n", 2);
		quit_prog(asmbly, 0);
	}
}
