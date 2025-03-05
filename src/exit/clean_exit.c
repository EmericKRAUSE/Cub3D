/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/02/18 21:07:40 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

//void free_map(t_map *map)
//{
//    if (map)
//    {
//        if (map->tab)
//            free_tab(&map->tab);
//        free(map);
//    }
//}

void clean_exit(t_game *game, char *msg, int exit_code)
{
    int i;
    char *next_line;

    if (game)
    {
        next_line = get_next_line(game->fd);
        while (next_line)
        {
            free(next_line);
            next_line = get_next_line(game->fd);
        }
        close(game->fd);
        free_tab(game->map.tab);
        if (game->mlx)
            mlx_terminate(game->mlx);
        i = 0;
        while (i < 4)
        {
            if (game->textures.f_names[i])
                free(game->textures.f_names[i]);
            i++;
        }
        free(game);
    }
    exit(ft_error(msg, exit_code));
}