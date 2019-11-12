/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gly <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 15:15:02 by gly               #+#    #+#             */
/*   Updated: 2019/10/29 18:54:30 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_process_data(t_corewar *cor, int player_nb)
{
	unsigned int i;

	i = -1;
	ft_printf("\n\n");
	ft_printf("-------------------------------------------------------\n");
	ft_printf("-> Player: [%d]\n\n", player_nb);
	ft_printf("\t=>prog_name = [%s]\n", cor->process[player_nb].name);
	ft_printf("\t=>comment   = [%s]\n", cor->process[player_nb].comment);
	ft_printf("\t=>prog_size = [%u]\n", cor->process[player_nb].size);
	ft_printf("\t=>magic     = [%u]\n", cor->process[player_nb].magic);
	ft_printf("\t=>Code:     =\n\n");
	while (++i < cor->process[player_nb].size)
	{
		ft_printf("%02x", cor->process[player_nb].code[i]);
		if (i % 9 == 1)
			ft_printf("\n");
	}
	ft_printf("\n-------------------------------------------------------");
	ft_printf("\n\n\n");
}

void	print_arena_state(t_corewar *cor)
{
	int p;
	int j;
	int i;

	j = 0;
	p = 0;
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (j == 64 || i == 0)
		{
			if (i != 0)
				ft_putchar('\n');
			ft_printf("0x%.4x : ", p);
			p += 64;
			j = 0;
		}
		ft_printf("%.2x ", cor->arena[i]);
		j++;
	}
	ft_printf("\n");
}

void	corewar_usage(void)
{
	ft_putstr_fd("Usage: ./corewar [-n N] [-dump N -v N | -visu --stealth] [-a]", 2);
	ft_putstr_fd(" <champion.cor> <...>\n\n", 2);
	ft_putstr_fd("    -a        : Prints output from \"aff\" \
			(Default is to hide it)\n", 2);
	ft_putstr_fd("    -n N      : Assign order N to next champion ", 2);
	ft_putstr_fd("(default : first champ is first to play)\n", 2);
	ft_putstr_fd("    -dump N   : Dumps memory after N cycles then exits\n", 2);
	ft_putstr_fd("    -v N      : Verbosity levels, \
			can be added together to enable several\n", 2);
	ft_putstr_fd("\t\t\t- 0 : Show only essentials\n", 2);
	ft_putstr_fd("\t\t\t- 1 : Show lives\n", 2);
	ft_putstr_fd("\t\t\t- 2 : Show cycles\n", 2);
	ft_putstr_fd("\t\t\t- 4 : Show operations \
			(Params are NOT litteral ...)\n", 2);
	ft_putstr_fd("\t\t\t- 8 : Show deaths\n", 2);
	ft_putstr_fd("\t\t\t- 16 : Show PC movements (Except for jumps)\n", 2);
	ft_putstr_fd("    -visu     : Ncurse visual\n", 2);
	ft_putstr_fd("    --stealth : Competition mode, \
			hide code with visual\n", 2);
}

void	corewar_quit(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	exit(EXIT_SUCCESS);
}
