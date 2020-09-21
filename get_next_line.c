/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhilary <fhilary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 16:28:43 by fhilary           #+#    #+#             */
/*   Updated: 2020/09/21 12:00:16 by fhilary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(const int fd, char **line)
{
	static char	*c[2147483647];
	char		buffer[BUFF_SIZE + 1];
	char		*tmp;
	ssize_t		b;
	char		*endl;

	if (fd < 0 || (!c[fd] && !(c[fd] = ft_strnew(1))) || !line
			|| (BUFF_SIZE < 0))
		return (-1);
	while (!ft_strchr(c[fd], '\n') && (b = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[b] = '\0';
		tmp = c[fd];
		if (!(c[fd] = ft_strjoin(c[fd], buffer)))
			return (-1);
		free(tmp);
	}
	if (b == -1 || !*(tmp = c[fd]))
		return (b == -1 ? -1 : 0);
	endl = ft_strchr(c[fd], '\n');
	*line = (endl ? ft_strsub(c[fd], 0, endl - c[fd]) : ft_strdup(c[fd]));
	c[fd] = (endl ? ft_strsub(c[fd], ft_strlen(*line) + 1,
						ft_strlen(endl) - 1) : NULL);
	free(tmp);
	return (!(!c[fd] && !ft_strlen(*line)));
}
