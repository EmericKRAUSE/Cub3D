/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:28:13 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/17 19:33:54 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	extract_line(char *stash, char **line)
{
    char	*ptr;

    ptr = ft_strchr(stash, '\n');
    *line = ft_strndup(stash, ptr - stash);
    ft_memmove(stash, ptr + 1, ft_strlen(ptr + 1) + 1);
}

void	refresh_buff(char *buff)
{
    ft_memmove(buff, buff + ft_strlen(buff), BUFFER_SIZE - ft_strlen(buff));
    buff[BUFFER_SIZE - 1] = '\0';
}

int	read_and_add(int fd, char **line, char *buff)
{
    int     ret;
    char    *tmp;

   while (ft_strchr(*line, '\n') == NULL || ret <= 0)
    {
       ret = read(fd, buff, BUFFER_SIZE);
       if (ret < 0)
       {
           free(*line);
           *line = NULL;
           return (ret);
       }
       buff[ret] = '\0';
       extract_line(buff, line);
       tmp = *line;
       *line = ft_strjoin(*line, buff);
       free(tmp);
   }
    return (ret);
}

char	*get_next_line(int fd)
{
    static char	buff[BUFFER_SIZE];
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
    refresh_buff(buff);
    return (line);
}
