/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:48:17 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/14 22:48:39 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		write_file(unsigned char *content, char *output_file,
			size_t output_len)
{
	int ret;

	ret = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (ret == -1)
	{
		ft_dprintf(2, "Enc: error creating file %s, %s\n",
			output_file, strerror(errno));
		exit(EXIT_FAILURE);
	}
	if ((write(ret, content, output_len)) == -1)
	{
		ft_dprintf(2, "Enc: error writing file %s, %s\n",
			output_file, strerror(errno));
		exit(EXIT_FAILURE);
	}
	close(ret);
}

void		write_stdin(unsigned char *content, size_t output_len)
{
	if ((write(1, content, output_len)) == -1)
	{
		ft_dprintf(2, "Enc: error writing to stdin, %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}
