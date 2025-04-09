/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:28:13 by ekrause           #+#    #+#             */
/*   Updated: 2025/04/09 13:08:05 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

void	extract_line(char *stash, char **line)
{
	char	*ptr;
	int		size;

	ptr = ft_strchr(stash, '\n');
	if (ptr)
		size = ptr - stash + 1;
	else
		size = BUFFER_SIZE;
	*line = ft_strndup(stash, size);
	if (ptr)
		ft_memmove(stash, ptr + 1, ft_strlen(ptr + 1) + 1);
	else
		stash[0] = '\0';
}

int	read_and_add(int fd, char **line, char *buff)
{
	int		ret;
	char	*tmp;
	char	*old_line;

	ret = 1;
	extract_line(buff, line);
	while (ft_strchr(*line, '\n') == NULL && ret > 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret < 0)
		{
			free(*line);
			*line = NULL;
			return (ret);
		}
		buff[ret] = '\0';
		extract_line(buff, &tmp);
		old_line = *line;
		*line = ft_strjoin(*line, tmp);
		free(old_line);
		free(tmp);
	}
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*line;

	line = NULL;
	if (ft_strchr(buff, '\n'))
		extract_line(buff, &line);
	else
		read_and_add(fd, &line, buff);
	if (line && !line[0])
	{
		free(line);
		line = NULL;
	}
	return (line);
}
