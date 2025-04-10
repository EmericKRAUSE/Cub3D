/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:29:00 by ekrause           #+#    #+#             */
/*   Updated: 2025/04/10 18:05:49 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

void clean_get_next_line(t_game *game)
{
    char *next_line;

    if (game->fd <= 0)
        return ;

    next_line = get_next_line(game->fd);
    while (next_line)
    {
        free(next_line);
        next_line = get_next_line(game->fd);
    }
    close(game->fd);
}