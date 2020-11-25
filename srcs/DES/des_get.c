/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:20:38 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/31 21:23:32 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void			des_get_pass(t_des *des)
{
	char *verify;

	if (!(des->pass = ft_strdup(getpass("enter des encryption password:"))))
		exit(EXIT_FAILURE);
	if (des->flags & FLAG_DES_E)
	{
		if (!(verify = ft_strdup(getpass("Verifying - enter des "
		"encryption password:"))))
			exit(EXIT_FAILURE);
		if (ft_strcmp(des->pass, verify))
			free_quit_pass(des, verify);
		free(verify);
	}
}

static void			check_data(t_des *des)
{
	if (des->salt_str && !ft_str_valid_hex(des->salt_str))
		free_quit_checkdata(des, "error: Salt non-hex digit\n");
	if (des->key && !ft_str_valid_hex(des->key))
		free_quit_checkdata(des, "error: Key non-hex digit\n");
	if (des->des_type != ECB && des->iv && !ft_str_valid_hex(des->iv))
		free_quit_checkdata(des, "error: IV non-hex digit\n");
}

static void			print_vars(t_des *des)
{
	if (des->des_type == ECB && des->iv)
		ft_putstr_fd("warning: iv not use by this cipher\n", 2);
	ft_printf("salt=%.16llX\n", des->salt_format);
	ft_printf("key=%.16llX\n", des->key_format);
	if (des->des_type != ECB)
		ft_printf("iv=%.16llX\n", des->iv_format);
}

void				get_data_and_check(t_des *des)
{
	int	encrypt;

	if (!des->pass && !des->key)
		des_get_pass(des);
	if (des->des_type != ECB && des->key && !des->iv && !des->pass)
	{
		ft_dprintf(2, "iv undefined\n");
		free_needed(des);
		exit(EXIT_FAILURE);
	}
	if (des->key || des->salt_str || des->iv)
		check_data(des);
	key_get_format(des);
	if (des->flags & FLAG_DES_P_MAJ)
		print_vars(des);
	encrypt = ((des->flags & FLAG_DES_E) || (des->des_type == CFB)) ? 1 : -1;
	create_subkeys(des, encrypt);
}
