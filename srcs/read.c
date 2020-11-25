/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:50:58 by hlombard          #+#    #+#             */
/*   Updated: 2020/10/29 09:17:44 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static unsigned char	*open_and_allocate(char *file, int *fd)
{
	unsigned char *str;

	if ((*fd = open(file, O_RDONLY)) < 0)
	{
		ft_dprintf(2, "Can't open %s for reading, %s\n", file, strerror(errno));
		return (NULL);
	}
	str = (unsigned char*)ft_strnew(0);
	return (str);
}

static unsigned char	*add_buffer(unsigned char const *s1,
						unsigned char const *s2, int len_s1, int len_s2)
{
	unsigned char	*str;
	int				i;

	if (!s1 || !s2)
		return (NULL);
	if (!(str = (unsigned char*)malloc(sizeof(unsigned char)
	* (len_s1 + len_s2 + 1))))
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

unsigned char			*read_stdin(size_t *size)
{
	int				ret;
	unsigned char	buf[BUFFSIZE];
	unsigned char	*str;
	unsigned char	*tmp;

	*size = 0;
	if (!(str = (unsigned char*)ft_strnew(0)))
		failed_allocate_exit("Couldn't allocate str\n");
	while ((ret = read(0, &buf, BUFFSIZE)) > 0)
	{
		tmp = str;
		if (!(str = add_buffer(tmp, buf, (int)*size, ret)))
			exit(EXIT_FAILURE);
		*size += ret;
		free(tmp);
	}
	if (ret == -1)
	{
		ft_dprintf(2, "Can't read stdin, %s\n", strerror(errno));
		free(str);
		return (NULL);
	}
	return (str);
}

unsigned char			*read_file(char *file, size_t *size)
{
	int				fd;
	int				ret;
	unsigned char	buf[BUFFSIZE];
	unsigned char	*str;
	unsigned char	*tmp;

	*size = 0;
	if (!(str = open_and_allocate(file, &fd)))
		return (NULL);
	while ((ret = read(fd, &buf, BUFFSIZE)) > 0)
	{
		tmp = str;
		if (!(str = add_buffer(tmp, buf, *size, ret)))
			exit(EXIT_FAILURE);
		*size += ret;
		free(tmp);
	}
	if (ret == -1 || close(fd) == -1)
	{
		ft_dprintf(2, "Can't read %s, %s\n", file, strerror(errno));
		free(str);
		return (NULL);
	}
	return (str);
}

unsigned char			*read_n_chars(t_des *des, size_t len)
{
	int				fd;
	size_t			ret;
	unsigned char	*str;

	fd = 0;
	if (des->input_file)
		fd = open(des->input_file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (!(str = (unsigned char*)ft_strnew(len + 1)))
		exit(EXIT_FAILURE);
	ret = read(fd, str, len);
	if (ret < 24)
	{
		free(str);
		free_needed(des);
		failed_allocate_exit("error reading input file\n");
	}
	if (des->input_file)
		close(fd);
	return (str);
}
