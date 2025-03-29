/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_line_fixed.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/29 21:40:42 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

char *make_char_line(char c, int len)
{
    char	*line;
    int		i;

    i = 0;
    line = ft_calloc(len + 1, sizeof(char));
    if (line)
        while (i < len)
            line[i++] = c;
    return (line);
}

// note: append_trab also free
char	**add_wall_up_and_down(char ***map_addr, char c_surround)
{
    char	**map;
    char	**new_map;
    char	*line;
    int 		i;

    map = *map_addr;
    if (!map)
        return (NULL);
    new_map = NULL;
    line = make_char_line(c_surround, ft_strlen(map[0]));
    new_map = append_tab(new_map, line);
    i = 0;
    while (map[i])
    {
        new_map = append_tab(new_map, map[i]);
        i++;
    }
    line = make_char_line(c_surround, ft_strlen(map[i - 1]));
    new_map = append_tab(new_map, line);
    *map_addr = new_map;
    return (new_map);
}

char	**add_wall_right_and_left(char ***map_addr, char c_surround) {
    char **map;
    char *line;
    int i;

    map = *map_addr;
    if (!map)
        return (NULL);
    i = 0;
    while (map[i]) {
        line = ft_calloc(ft_strlen(map[i]) + 3, sizeof(char));
        line[0] = c_surround;
        ft_strlcpy(line + 1, map[i], ft_strlen(map[i]) + 1);
        line[ft_strlen(map[i])] = c_surround;
        line[ft_strlen(map[i]) + 1] = '\0';
        free(map[i]);
        map[i] = line;
        i++;
    }
    return (map);
}

void surround_map(char ***map_addr, char c_surround)
{
    char	**map;

    map = *map_addr;
    map = add_wall_up_and_down(&map, c_surround);
    map = add_wall_right_and_left(&map, c_surround);
    *map_addr = map;
}