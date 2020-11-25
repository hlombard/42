/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 23:03:50 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/14 23:03:52 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	flags_classics(char **av, int i, t_hash *hash)
{
	if (!ft_strcmp("-p", av[i]))
	{
		hash->flags |= FLAG_HASH_P;
		hash->flag_p++;
		return (1);
	}
	else if (!ft_strcmp("-q", av[i]))
	{
		hash->flags |= FLAG_HASH_Q;
		return (1);
	}
	else if (!ft_strcmp("-r", av[i]))
	{
		hash->flags |= FLAG_HASH_R;
		return (1);
	}
	else
	{
		return (0);
	}
}

void		hash_flags_set(int ac, char **av, int i, t_hash *hash)
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
				hash->flags |= FLAG_HASH_S;
				hash->flag_s_pos = i;
			}
			break ;
		}
	}
	if (!(hash->flags & FLAG_HASH_S) && ac - i <= 0)
		hash->no_file = 0;
	hash->arg_index = i;
}

int			flags_p_special(t_hash *hash)
{
	if (hash->flags & FLAG_HASH_P)
	{
		hash->read = 0;
		g_hash[hash->hash_type].hashfunc("", hash);
		g_hash[hash->hash_type].printfunc(NULL, hash);
	}
	else
	{
		hash->flags |= FLAG_HASH_P;
		hash_read_input(NULL, hash);
	}
	return (1);
}

int			flags_set_q_r(char **av, t_hash *hash)
{
	if (!ft_strcmp("-q", av[hash->arg_index]))
		hash->flags |= FLAG_HASH_Q;
	else if (!ft_strcmp("-r", av[hash->arg_index]))
		hash->flags |= FLAG_HASH_R;
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
