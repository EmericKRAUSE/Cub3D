/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:03:26 by supersko          #+#    #+#             */
/*   Updated: 2024/11/03 20:09:17 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# ifndef MAX_FD
#  define MAX_FD 256
# endif
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>

void	format_buff(char *buff, char *next_line);
void	append_line(char *buff, char **next_line);
char	*line_from_buff(char *buff);
char	*load_until_line(int fd, char *buff);
char	*get_next_line(int fd);
void	get_next_line_tester(int argc, char **argv);

#endif
