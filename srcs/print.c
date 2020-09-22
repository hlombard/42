/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 13:48:26 by hlombard          #+#    #+#             */
/*   Updated: 2020/09/15 21:57:45 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	print_before_hash(char *name, int type, t_hash *hash)
{
	if (name != NULL && !(hash->flags & FLAG_Q) && !(hash->flags & FLAG_R))
	{
		ft_printf("%s (", get_name(type, hash));
		if (hash->print_quotes)
			ft_putchar('"');
		ft_putstr(name);
		if (hash->print_quotes)
		{
			ft_putchar('"');
			hash->print_quotes = 0;
		}
		ft_putstr(") = ");
	}
}

static void	print_after_hash(char *name, t_hash *hash)
{
	if (name != NULL && !(hash->flags & FLAG_Q) && (hash->flags & FLAG_R))
	{
		ft_putchar(' ');
		if (hash->print_quotes)
			ft_putchar('"');
		ft_putstr(name);
		if (hash->print_quotes)
		{
			ft_putchar('"');
			hash->print_quotes = 0;
		}
	}
	ft_putchar('\n');
}

void		print_md5(char *name, t_hash *hash)
{
	uint8_t *p;

	print_before_hash(name, 1, hash);
	p = (uint8_t *)&hash->h_32[0];
	ft_printf("%02x%02x%02x%02x", p[0], p[1], p[2], p[3]);
	p = (uint8_t *)&hash->h_32[1];
	ft_printf("%02x%02x%02x%02x", p[0], p[1], p[2], p[3]);
	p = (uint8_t *)&hash->h_32[2];
	ft_printf("%02x%02x%02x%02x", p[0], p[1], p[2], p[3]);
	p = (uint8_t *)&hash->h_32[3];
	ft_printf("%02x%02x%02x%02x", p[0], p[1], p[2], p[3]);
	print_after_hash(name, hash);
}

void		print_sha256(char *name, t_hash *hash)
{
	print_before_hash(name, 1, hash);
	ft_printf("%08x%08x%08x%08x%08x%08x%08x", hash->h_32[0],
	hash->h_32[1], hash->h_32[2], hash->h_32[3], hash->h_32[4],
	hash->h_32[5], hash->h_32[6]);
	if (!ft_strcmp(g_hash[hash->algo_type].name, "sha256"))
		ft_printf("%08x", hash->h_32[7]);
	print_after_hash(name, hash);
}

void		print_sha512(char *name, t_hash *hash)
{
	print_before_hash(name, 1, hash);
	ft_printf("%016llx", hash->h_64[0]);
	ft_printf("%016llx", hash->h_64[1]);
	ft_printf("%016llx", hash->h_64[2]);
	ft_printf("%016llx", hash->h_64[3]);
	ft_printf("%016llx", hash->h_64[4]);
	ft_printf("%016llx", hash->h_64[5]);
	if (!ft_strcmp(g_hash[hash->algo_type].name, "sha512"))
		ft_printf("%016llx%016llx", hash->h_64[6], hash->h_64[7]);
	print_after_hash(name, hash);
}
