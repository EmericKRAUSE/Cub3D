/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/12 11:21:50 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

int is_out_of_bounds(char **map, int y, int x)
{
    if (y < 0 || x < 0)
        return (TRUE);
    if (map[y] == NULL)
        return (TRUE);
    if (map[y][x] == '\0')
        return (TRUE);
    return (FALSE);
}

int floodfill(char **map, int y, int x)
{
    if (is_out_of_bounds(map, y, x))
        return (FALSE);
    if (ft_strchr(BLANK_CHAR, map[y][x]))
        return (FALSE);
    if (map[y][x] == CHAR_BLANK_MAP)
        return (FALSE);
    if (map[y][x] == FLOODFILL_VISITED)
        return (TRUE);
    if (ft_strchr(FLOODFILL_CHARS, map[y][x]))
    {
        map[y][x] = FLOODFILL_VISITED;
        if (floodfill(map, y + 1, x))
            if (floodfill(map, y - 1, x))
                if (floodfill(map, y, x + 1))
                    if (floodfill(map, y, x - 1))
                        return (TRUE);
        return (FALSE);
    }
    return (TRUE);
}

int is_map_closed(char **map)
{
    t_point pos_player;
    char **map_cpy;
    int is_closed;

    map_cpy = dup_tab(map);
    pos_player = get_player_position(map_cpy);
    is_closed = floodfill(map_cpy, pos_player.y, pos_player.x);
    if (!is_closed)
        printf("[is_map_closed] map not closed\n");
    ft_free_split(&map_cpy);
    return (is_closed);
}
