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
    if (game)
        free_tab(game->map.tab);
    if (game->mlx)
        mlx_terminate(game->mlx);
    exit(ft_error(msg, exit_code));
}