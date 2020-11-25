/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 01:53:48 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/24 14:08:29 by hlombard         ###   ########.fr       */
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
	i = -1;
	while (g_enc[++i].name != NULL)
		ft_dprintf(2, "%s\n", g_enc[i].name);
	i = -1;
	while (g_des[++i].name != NULL)
		ft_dprintf(2, "%s\n", g_des[i].name);
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
