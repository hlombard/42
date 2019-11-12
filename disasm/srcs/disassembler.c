/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassembler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 17:17:00 by ratin             #+#    #+#             */
/*   Updated: 2019/09/05 17:07:44 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassembler.h"

uint32_t			swap_endian(uint32_t val)
{
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return ((val << 16) | (val >> 16));
}

void				decomp_quit(t_corewar *cor, char *str)
{
	ft_putstr_fd(str, 2);
	free(cor->code);
	exit(1);
}

int					cor_file(char *av)
{
	int			i;

	i = ft_strlen(av);
	if (i <= 4)
		return (-1);
	i -= 4;
	if (ft_strncmp(&av[i], ".cor", 4))
		return (-1);
	else
		return (1);
}

static inline void	init_datas(t_corewar *cor)
{
	ft_bzero(cor, sizeof(t_corewar));
}

int					main(int ac, char **av)
{
	t_corewar	cor;

	if (ac != 2 || cor_file(av[1]) == -1)
	{
		ft_putstr_fd("Usage: ./disassembler <file.cor>\n", 2);
		exit(ERROR);
	}
	init_datas(&cor);
	read_process(av[1], &cor);
	create_file(&cor, av[1]);
	free(cor.code);
	return (0);
}
