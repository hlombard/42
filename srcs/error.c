/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 00:10:09 by hlombard          #+#    #+#             */
/*   Updated: 2020/09/16 01:30:43 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		error_command(char *str)
{
	int i;

	i = -1;
	ft_dprintf(2, "ft_ssl: Error: '%s' is an invalid command.\n\n", str);
	ft_dprintf(2, "Standard commands:\n\n");
	ft_dprintf(2, "Message Digest commands:\n");
	while (g_hash[++i].name != NULL)
		ft_dprintf(2, "%s\n", g_hash[i].name);
	ft_dprintf(2, "\nCypher commands:\n");
}

void		error_stdin(t_hash *hash, char *str)
{
	ft_dprintf(2, "ft_ssl: %s: %s: %s\n", get_name(0, hash),
		"(stdin)", "fatal error");
	free(str);
	exit(EXIT_FAILURE);
}

void		quit_s_option_error(t_hash *hash)
{
	ft_dprintf(2, "ft_ssl: %s: option requires an argument --s\n",
		get_name(0, hash));
	ft_dprintf(2, "usage: %s [-pqr] [-s string] [files ...]\n",
		get_name(0, hash));
	exit(EXIT_FAILURE);
}

void		failed_allocate_exit(char *str)
{
	ft_putstr_fd(str, 2);
	exit(EXIT_FAILURE);
}
