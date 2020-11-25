/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:42:57 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/23 17:19:10 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void				free_quit_pass(t_des *des, char *str)
{
	ft_putstr_fd("Verify failure\n", 1);
	ft_putstr_fd("bad password read\n", 2);
	free(des->pass);
	free(str);
	if (des->salt_str)
		free(des->salt_str);
	exit(EXIT_FAILURE);
}

void				free_quit_checkdata(t_des *des, char *str)
{
	ft_putstr_fd(str, 2);
	if (des->salt_str)
		free(des->salt_str);
	if (des->pass)
		free(des->pass);
	exit(EXIT_FAILURE);
}

void				free_needed(t_des *des)
{
	if (des->pass)
		free(des->pass);
	if (des->salt_str)
		free(des->salt_str);
}
