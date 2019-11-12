/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 23:26:51 by ratin             #+#    #+#             */
/*   Updated: 2019/09/05 01:59:41 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassembler.h"

void	print_header(t_corewar *cor)
{
	ft_putstr_fd(NAME_CMD_STRING " \"", cor->fd);
	ft_putstr_fd(cor->name, cor->fd);
	ft_putstr_fd("\"\n", cor->fd);
	ft_putstr_fd(COMMENT_CMD_STRING " \"", cor->fd);
	ft_putstr_fd(cor->comment, cor->fd);
	ft_putstr_fd("\"\n", cor->fd);
	ft_putstr_fd("\n", cor->fd);
}

void	print_file(t_corewar *cor)
{
	print_header(cor);
	create_list(cor);
}
