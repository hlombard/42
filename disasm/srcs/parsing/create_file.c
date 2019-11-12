/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 23:10:08 by ratin             #+#    #+#             */
/*   Updated: 2019/09/05 02:17:55 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassembler.h"

void	create_file(t_corewar *cor, char *name)
{
	char		*path;

	if (!(path = ft_strndup(name, ft_strlen(name) - 4)))
		decomp_quit(cor, "error ft_strndup\n");
	if (!(path = ft_strjoin_free(path, ".s", 1)))
		decomp_quit(cor, "error ft_strjoin_free\n");
	cor->fd = open(path, O_WRONLY | O_APPEND | O_CREAT | O_TRUNC, 0644);
	free(path);
	if (cor->fd == -1)
		decomp_quit(cor, "error when creating the file\n");
	print_file(cor);
	ft_putstr("decompiled file at ");
	if (!(path = ft_strndup(name, ft_strlen(name) - 4)))
		decomp_quit(cor, "error ft_strndup\n");
	ft_putstr(path);
	ft_putstr(".s");
	ft_putstr("\n");
	free(path);
}
