/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 13:46:38 by hlombard          #+#    #+#             */
/*   Updated: 2020/09/16 12:28:19 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	flags_classics(char **av, int i, t_hash *hash)
{
	if (!ft_strcmp("-p", av[i]))
	{
		hash->flags |= FLAG_P;
		hash->flag_p++;
		return (1);
	}
	else if (!ft_strcmp("-q", av[i]))
	{
		hash->flags |= FLAG_Q;
		return (1);
	}
	else if (!ft_strcmp("-r", av[i]))
	{
		hash->flags |= FLAG_R;
		return (1);
	}
	else
	{
		return (0);
	}
}

void		flags_set(int ac, char **av, int i, t_hash *hash)
{
	hash->no_file = 1;
	while (++i < ac)
	{
		if (flags_classics(av, i, hash))
			continue;
		else
		{
			if (!ft_strcmp("-s", av[i]))
			{
				hash->flags |= FLAG_S;
				hash->flag_s_pos = i;
			}
			break ;
		}
	}
	if (!(hash->flags & FLAG_S) && ac - i <= 0)
		hash->no_file = 0;
	hash->arg_index = i;
}

int			flags_p_special(t_hash *hash)
{
	if (hash->flags & FLAG_P)
	{
		hash->read = 0;
		g_hash[hash->algo_type].hashfunc("", hash);
		g_hash[hash->algo_type].printfunc(NULL, hash);
	}
	else
	{
		hash->flags |= FLAG_P;
		read_input(NULL, hash);
	}
	return (1);
}

int			flags_set_q_r(char **av, t_hash *hash)
{
	if (!ft_strcmp("-q", av[hash->arg_index]))
		hash->flags |= FLAG_Q;
	else if (!ft_strcmp("-r", av[hash->arg_index]))
		hash->flags |= FLAG_R;
	return (1);
}

void		flags_available(void)
{
	ft_printf("usage: ./ft_ssl [algo] [-flags] [file...]\n");
	ft_printf("\nFlags available:\n");
	ft_printf("\t-p : echo STDIN to STDOUT and append the "
	"checksum to STDOUT\n");
	ft_printf("\t-q : quiet mode\n");
	ft_printf("\t-r : reverse the format of the output\n");
	ft_printf("\t-s : print the sum of the given string\n");
}
