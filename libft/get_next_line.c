/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <hlombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:06:11 by hlombard          #+#    #+#             */
/*   Updated: 2019/12/09 18:21:12 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "./includes/ft_printf.h"

void	ft_nextline2(char **str, char **line, int fd, int len)
{
	char	*tmp;

	tmp = NULL;
	*line = ft_strsub(str[fd], 0, len);
	tmp = ft_strdup(str[fd] + len + 1);
	free(str[fd]);
	str[fd] = tmp;
	if (str[fd][0] == '\0')
		ft_strdel(&str[fd]);
}

int		ft_nextline(char **str, char **line, int fd, int nbbytes)
{
	int		len;

	len = 0;
	while (str && str[fd] && str[fd][len] != '\n' && str[fd][len] != '\0')
		len++;
	if (str && str[fd] && str[fd][len] && str[fd][len] == '\n')
		ft_nextline2(str, line, fd, len);
	else if (str && str[fd] && str[fd][len] && str[fd][len] == '\0')
	{
		if (nbbytes == BUFF_SIZE)
			return (get_next_line(fd, line, 0, 0));
		free(*line);
		*line = ft_strdup(str[fd]);
		ft_strdel(&str[fd]);
	}
	else if (str[fd])
	{
		*line = ft_strdup(str[fd]);
		ft_strdel(&str[fd]);
	}
	return (1);
}

int		gnl(char **str, int fd, int i)
{
	ft_strdel(&str[fd]);
	i = 10;
	return (0);
}

int		get_next_line2(char buf[BUFF_SIZE + 1], char **str, int fd, char **l)
{
	if (buf[0] == '\0')
	{
		ft_strdel(&str[fd]);
		if (*l)
			free(*l);
		return (-1);
	}
	return (1);
}

int		get_next_line(const int fd, char **line, int i, int nbby)
{
	static char	*str[200];
	char		buf[BUFF_SIZE + 1];
	char		*tmp;

	if (fd < 0 || !line || (i == -10 && !(gnl(str, fd, i))))
		return (-1);
	while ((nbby = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if (get_next_line2(buf, str, fd, line) == -1)
			return (0);
		buf[nbby] = '\0';
		if (str[fd] == NULL)
			str[fd] = ft_strnew(1);
		tmp = str[fd];
		str[fd] = ft_strjoin(tmp, buf);
		free(tmp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (nbby < 0)
		return (-1);
	else if ((nbby == 0) && ((str[fd] == NULL) || (str[fd][0] == '\0')))
		return (0);
	return (ft_nextline(str, line, fd, nbby));
}
