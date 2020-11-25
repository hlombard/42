/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 23:01:54 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/14 23:02:11 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		hash_read_input(char *str, t_hash *hash)
{
	str = (char*)read_stdin(&hash->read);
	if (!ft_strcmp("help\n", str))
	{
		flags_available();
		free(str);
		return ;
	}
	if (hash->flags & FLAG_HASH_P)
		ft_putstr(str);
	g_hash[hash->hash_type].hashfunc(str, hash);
	g_hash[hash->hash_type].printfunc(NULL, hash);
	while (hash->flag_p-- > 1)
	{
		hash->read = 0;
		g_hash[hash->hash_type].hashfunc("", hash);
		g_hash[hash->hash_type].printfunc(NULL, hash);
	}
	free(str);
}

static char	*add_buffer(char const *s1, char const *s2, int len_s1, int len_s2)
{
	char	*str;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	if (!(str = (char*)malloc(sizeof(char) * (len_s1 + len_s2 + 1))))
		return (NULL);
	i = -1;
	while (++i < len_s1)
		str[i] = s1[i];
	i = -1;
	while (++i < len_s2)
	{
		str[len_s1] = s2[i];
		len_s1++;
	}
	return (str);
}

static char	*open_and_allocate(char *file, int *fd, t_hash *hash)
{
	char *str;

	if ((*fd = open(file, O_RDONLY)) < 0)
	{
		ft_dprintf(2, "ft_ssl: %s: %s: %s\n", get_name(0, hash),
			file, strerror(errno));
		return (NULL);
	}
	str = ft_strnew(0);
	hash->read = 0;
	return (str);
}

char		*hash_read_file(char *file, t_hash *hash)
{
	int		fd;
	int		ret;
	char	buf[BUFFSIZE];
	char	*str;
	char	*tmp;

	if (!(str = open_and_allocate(file, &fd, hash)))
		return (NULL);
	while ((ret = read(fd, &buf, BUFFSIZE)) > 0)
	{
		tmp = str;
		if (!(str = add_buffer(tmp, buf, hash->read, ret)))
			exit(EXIT_FAILURE);
		hash->read += ret;
		free(tmp);
	}
	if (ret == -1 || close(fd) == -1)
	{
		ft_dprintf(2, "ft_ssl: %s: %s: %s\n", get_name(0, hash),
			file, strerror(errno));
		free(str);
		return (NULL);
	}
	return (str);
}

const char	*get_name(int type, t_hash *hash)
{
	if (type)
		return (g_hash[hash->hash_type].bigname);
	return (g_hash[hash->hash_type].name);
}
