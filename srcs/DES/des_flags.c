/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:41:53 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/24 00:06:08 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int		next_arg(char *arg, char *next)
{
	if (!next)
	{
		ft_dprintf(2, "enc: Option %s needs a value\n", arg);
		exit(EXIT_FAILURE);
	}
	return (1);
}

static int		des_flags_check1(char **av, int *i, t_des *des)
{
	if (ft_strcmp(av[*i], "-a") && ft_strcmp(av[*i], "-d")
		&& ft_strcmp(av[*i], "-e") && ft_strcmp(av[*i], "-i"))
		return (0);
	if (!ft_strcmp(av[*i], "-a"))
		des->flags |= FLAG_DES_A;
	else if (!ft_strcmp(av[*i], "-d"))
	{
		des->flags |= FLAG_DES_D;
		des->flags &= ~(FLAG_DES_E);
	}
	else if (!ft_strcmp(av[*i], "-e"))
	{
		des->flags |= FLAG_DES_E;
		des->flags &= ~(FLAG_DES_D);
	}
	else
	{
		next_arg(av[*i], av[*i + 1]);
		des->flags |= FLAG_DES_I;
		des->input_file = av[++(*i)];
	}
	return (1);
}

static int		des_flags_check2(char **av, int *i, t_des *des)
{
	if (ft_strcmp(av[*i], "-k") && ft_strcmp(av[*i], "-o")
		&& ft_strcmp(av[*i], "-p") && ft_strcmp(av[*i], "-s"))
		return (0);
	if (!ft_strcmp(av[*i], "-k") && next_arg(av[*i], av[*i + 1]))
	{
		des->flags |= FLAG_DES_K;
		des->key = av[++(*i)];
	}
	else if (!ft_strcmp(av[*i], "-o") && next_arg(av[*i], av[*i + 1]))
	{
		des->flags |= FLAG_DES_O;
		des->output_file = av[++(*i)];
	}
	else if (!ft_strcmp(av[*i], "-p") && next_arg(av[*i], av[*i + 1]))
	{
		des->flags |= FLAG_DES_P;
		des->pass = ft_strdup(av[++(*i)]);
	}
	else
	{
		next_arg(av[*i], av[*i + 1]);
		des->flags |= FLAG_DES_S;
		des->salt_str = ft_strdup(av[++(*i)]);
	}
	return (1);
}

static int		des_flags_check3(char **av, int *i, t_des *des)
{
	if (ft_strcmp(av[*i], "-v") && ft_strcmp(av[*i], "-P")
		&& ft_strcmp(av[*i], "-nopad"))
		return (0);
	if (!ft_strcmp(av[*i], "-v") && next_arg(av[*i], av[*i + 1]))
	{
		des->flags |= FLAG_DES_V;
		des->iv = av[++(*i)];
	}
	else if (!ft_strcmp(av[*i], "-P"))
		des->flags |= FLAG_DES_P_MAJ;
	else
		des->flags |= FLAG_DES_NOPAD;
	return (1);
}

int				des_flags_set(int ac, char **av, t_des *des)
{
	int i;

	i = 1;
	des->flags |= FLAG_DES_E;
	while (++i < ac)
	{
		if (des_flags_check1(av, &i, des))
			continue;
		else if (des_flags_check2(av, &i, des))
			continue;
		else if (des_flags_check3(av, &i, des))
			continue;
		else
		{
			ft_dprintf(2, "enc: Unrecognized flag %s\n", av[i]);
			free_needed(des);
			exit(EXIT_FAILURE);
		}
	}
	return (1);
}
