/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratin <ratin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 20:17:57 by ratin             #+#    #+#             */
/*   Updated: 2019/09/05 16:40:40 by ratin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		init_prog(t_asm *asmbly)
{
	ft_bzero(asmbly, sizeof(asmbly));
	asmbly->name = NULL;
	ft_bzero(asmbly->comment, COMMENT_LENGTH + 1);
	asmbly->size = 0;
	asmbly->in_comment = 0;
	asmbly->got_comment = 0;
	asmbly->got_name = 0;
	asmbly->in_comment = 0;
	asmbly->idx_comment = 0;
	asmbly->instru = NULL;
}

void		print_writing(char *str)
{
	int		i;
	char	*new_file;

	i = 0;
	new_file = ft_strndup(str, ft_strlen(str) - 2);
	ft_putstr("Writing output program to ");
	ft_putstr(new_file);
	ft_putstr(".cor\n");
	free(new_file);
}

int			main(int ac, char **av)
{
	t_asm	asmbly;

	if (ac < 2)
	{
		ft_putstr_fd("Usage: ./asm <sourcefile.s>\n", 2);
		exit(ERROR);
	}
	init_prog(&asmbly);
	parse_file(&asmbly, av[ac - 1]);
	dlt_lst_empty_lbl(&asmbly);
	convert_instruction(&asmbly);
	count_size(&asmbly);
	write_file(&asmbly, av[ac - 1]);
	print_writing(av[ac - 1]);
	free_prog(&asmbly);
	return (0);
}
