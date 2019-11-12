/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_process1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 20:22:44 by ratin             #+#    #+#             */
/*   Updated: 2019/09/05 13:33:15 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassembler.h"

void	read_process(char *name, t_corewar *cor)
{
	t_header	header;
	int			fd;

	if ((fd = open(name, O_RDONLY)) < 0)
		decomp_quit(cor, "Open error\n");
	if ((read(fd, &header, sizeof(t_header)) < 0))
		decomp_quit(cor, "Read error\n");
	stock_process_name(cor, &header);
	stock_process_size(cor, &header);
	stock_process_comment(cor, &header);
	stock_process_magic(cor, &header);
	stock_process_code(cor, fd);
}
