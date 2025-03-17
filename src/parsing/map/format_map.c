/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/17 15:05:18 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

void    delete_blank_lines(char ***map_addr)
{
    ssize_t last_line;
    char **map = *map_addr;

    if (map == NULL)
        return ;
    last_line = ft_tablen(map) - 1;
    while (last_line && is_blank_line(map[last_line]))
    {
        free(map[last_line]);
        map[last_line] = NULL;
        last_line--;
    }
    if (last_line <= 0)
    {
        free(map[last_line]);
        free(map);
        map= NULL;
    }
    *map_addr = map;
}

int smallest_blank_gap_at_left_side(char **map)
{
    int smallest_gap = INT_MAX;
    int i;

    if (!map)
        return (-1);
    while (*map)
    {
        i = 0;
        while ((*map)[i] == ' ')
            i++;
        if (i < smallest_gap)
            smallest_gap = i;
        map++;
    }
    return (smallest_gap);
}

void shift_to_left(char ***map_addr)
{
    int smallest_gap;
    char **map;
    char *line;
    int		i;

    map = *map_addr;
    smallest_gap = smallest_blank_gap_at_left_side(map);
    i = 0;
    while (map[i])
    {
        line = map[i];
        while (line[smallest_gap])
        {
            *line = line[smallest_gap];
            line++;
        }
        *line = line[smallest_gap];
        i++;
    }
    *map_addr = map;
}

void ft_trim_right(char ***map_addr)
{
    int i;
    int j;
    char **map = *map_addr;

	if (!map)
		return ;
    i = 0;
    while (map[i])
    {
        j = ft_strlen(map[i]) - 1;
        while (ft_strchr(" \n", map[i][j]))
            j--;
        map[i][j + 1] = '\0';
        i++;
    }
    *map_addr = map;
}

void trim_map(char ***map_addr)
{
    delete_blank_lines(map_addr);
    if (*map_addr)
        shift_to_left(map_addr);
    ft_trim_right(map_addr);
}

void set_width_and_lenght(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (game->map.tab[i])
    {
        j = 0;
        j = ft_strlen(game->map.tab[i]);
        while (j >= 0)
        {
            if (!ft_strchr(" \n", game->map.tab[i][j]))
                break ;
            else
                j--;
        }

        if (j + 1> game->map.width)
            game->map.width = j + 1;
        i++;
    }
    game->map.height = i;
}

char **square_malloc(int width, int height)
{
    int i;
    char **tab;

    i = 0;
    tab = ft_calloc(sizeof(char *), height + 1);
    if (!tab)
        return (NULL);
    while (i < height)
    {
        tab[i] = ft_calloc(sizeof(char), width + 1);
        if (!tab[i])
        {
            ft_free_split(&tab);
            return (NULL);
        }
        i++;
    }
    tab[i] = NULL;
    return (tab);
}

void ft_square_map(t_game *game, char c)
{
    int i;
    int j;
    char **map = game->map.tab;
    char **new_map;

    i = 0;
    new_map = square_malloc(game->map.width, game->map.height);
    if (!new_map)
        clean_exit(game, "Error: malloc failed (ft_square_map)", ERR_MALLOC);
    while (i < game->map.height)
    {
        j = 0;
        while (j < game->map.width)
        {
            new_map[i][j] = c;
            if (j < (int)ft_strlen(map[i]))
                if (map[i][j] != ' ')
                    new_map[i][j] = map[i][j];
            j++;
        }
        i++;
    }
    ft_free_split(&game->map.tab);
    game->map.tab = new_map;
}

