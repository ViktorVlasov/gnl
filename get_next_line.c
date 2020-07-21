/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efumiko <efumiko@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 11:33:07 by efumiko           #+#    #+#             */
/*   Updated: 2020/07/21 13:32:09 by efumiko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*check_rem(char **remainder, char **line)
{
	char	*p_n;

	p_n = NULL;
	if (*remainder)
	{
		if ((p_n = ft_strchr(*remainder, '\n')))
		{
			*p_n = '\0';
			*line = ft_strdup(*remainder);
			p_n++;
			ft_strcpy(*remainder, p_n);
		}
		else
		{
			*line = ft_strdup(*remainder);
			free(*remainder);
			*remainder = NULL;
		}
	}
	else
		*line = ft_strdup("");
	return (p_n);
}

int			get_next_line(int fd, char **line)
{
	static char	*remainder;
	char		buf[BUFFER_SIZE + 1];
	int			count_byte;
	char		*p_n;
	char		*tmp;

	if (BUFFER_SIZE < 1 || fd < 0 || !line)
		return (-1);
	if (read(fd, buf, 0) < 0)
		return (-1);
	p_n = check_rem(&remainder, line);
	while (!p_n && (count_byte = read(fd, buf, BUFFER_SIZE)))
	{
		buf[count_byte] = '\0';
		if ((p_n = ft_strchr(buf, '\n')))
		{
			*p_n = '\0';
			remainder = ft_strdup(++p_n);
		}
		tmp = *line;
		if (!(*line = ft_strjoin(*line, buf)) || count_byte < 0)
			return (-1);
		free(tmp);
	}
	return ((p_n) ? 1 : 0);
}
