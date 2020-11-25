/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enc_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:53:55 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/25 18:16:11 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int			encoding_or_decoding(char *av, t_encoding *enc)
{
	if (!ft_strcmp(av, "-d"))
	{
		enc->flags |= FLAG_ENC_D;
		enc->flags &= ~(FLAG_ENC_E);
		return (1);
	}
	if (!ft_strcmp(av, "-e"))
	{
		enc->flags |= FLAG_ENC_E;
		enc->flags &= ~(FLAG_ENC_D);
		return (1);
	}
	if (!ft_strcmp(av, "-url"))
	{
		enc->flags |= FLAG_ENC_URL;
		return (1);
	}
	return (0);
}

static int			input_or_output(int *i, char **av, t_encoding *enc)
{
	if (!av[++(*i)])
	{
		ft_dprintf(2, "enc: Option %s needs a value\n", av[*i - 1]);
		return (0);
	}
	if (!ft_strcmp(av[(*i) - 1], "-i"))
	{
		enc->input_file = av[*i];
		enc->flags |= FLAG_ENC_I;
	}
	else
	{
		enc->output_file = av[*i];
		enc->flags |= FLAG_ENC_O;
	}
	return (1);
}

void				enc_flags_set(int ac, char **av, t_encoding *enc)
{
	int i;

	i = 1;
	enc->flags |= FLAG_ENC_E;
	while (++i < ac)
	{
		if (encoding_or_decoding(av[i], enc))
			continue;
		else if (!ft_strcmp(av[i], "-i") || !ft_strcmp(av[i], "-o"))
		{
			if (!input_or_output(&i, av, enc))
				exit(EXIT_FAILURE);
		}
		else
		{
			if (!ft_strncmp(av[i], "-", 1))
				ft_dprintf(2, "enc: Unrecognized flag %s\n", av[i]);
			else
				ft_dprintf(2, "enc: Extra arguments given\n");
			exit(EXIT_FAILURE);
		}
	}
}
