/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_cub_fixed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/13 19:15:44 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

char	*free_and_get_line(char	*line, int fd)
{
	free(line);
	return (get_next_line(fd));
}

void	process_line(t_game *game, char **line)
{
	if (is_blank_line(*line))
		*line = free_and_get_line(*line, game->fd);
	else if (is_map(*line))
		*line = load_map(game, *line);
	else if (is_texture(game, *line))
	{
		if (get_texture(game, *line) == ERR_LOADING_TEXTURE)
			clean_exit(game, "[get_texture] loading error", ERR_TEXTURE);
		*line = free_and_get_line(*line, game->fd);
	}
	else if (is_color(*line))
	{
		if (get_color(game, *line) == ERR_LOADING_TEXTURE)
			clean_exit(game, "[get_color] something went wrong", ERR_COLOR);
		*line = free_and_get_line(*line, game->fd);
	}
	else
		invalid_line(game, *line);
}

t_point get_player_position(char **map)
{
    t_point pos_player;

    pos_player.x = 0;
    pos_player.y = 0;
    while (map[pos_player.y])
    {
        pos_player.x = 0;
        while (map[pos_player.y][pos_player.x])
        {
            if (ft_strchr("NSWE", map[pos_player.y][pos_player.x]))
                return (pos_player);
            pos_player.x++;
        }
        pos_player.y++;
    }
    return (pos_player);
}

int one_player_only(char **map)
{
    t_point pos_player;
    char **map_copy;

    map_copy = dup_tab(map);
    pos_player = get_player_position(map_copy);
    if (map[pos_player.y] == NULL)
    {
        printf("[one_player_only] no player\n");
        free_tab(map_copy);
        return (FALSE);
    }
    set_map_point(map_copy, pos_player, '0');
    pos_player = get_player_position(map_copy);
    free_tab(map_copy);
    if (map[pos_player.y] == NULL)
        return (TRUE);
    printf("[one_player_only] more than one player\n");
    return (FALSE);
}

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
    //print_tab(map_cpy);
    free_tab(map_cpy);
    return (is_closed);
}

int is_map_available(t_game *game)
{
    if (game->map.tab == NULL)
        return (FALSE);
    if (!one_player_only(game->map.tab))
        return (FALSE);
    if (!is_map_closed(game->map.tab))
        return (FALSE);
    return (TRUE);
}

int param_missing(t_game *game)
{
    int i;

    i = 0;
    if (game->map.tab == NULL)
        clean_exit(game, "[param_missing] map is missing", ERR_MAP);
    if (game->textures.ceiling.r == UNSET_COLOR)
        clean_exit(game, "[param_missing] ceiling is missing", ERR_MAP);
    if (game->textures.floor.r == UNSET_COLOR)
        clean_exit(game, "[param_missing] floor is missing", ERR_MAP);
    while (i < 4)
    {
        if (game->textures.f_names[i] == NULL)
            clean_exit(game, "[param_missing] texture is missing", ERR_MAP);
        i++;
    }
    return (FALSE);
}

int	import_cub_file(t_game *game)
{
	char	*line;

	line = get_next_line(game->fd);
	game->map.tab = NULL;
	while (line)
	{
        process_line(game, &line);
    }
    if (!is_map_available(game))
    {
        clean_exit(game, "[import_cub_file] map not available", ERR_MAP);
    }
	if (param_missing(game))
    {
        clean_exit(game, "[import_cub_file] param missing", ERR_MAP);
    }
	game->map.width = ft_strlen(game->map.tab[0]);
	game->map.height = tab_len(game->map.tab);
    return (TRUE);
}

int	is_cub_file(char *filename)
{
	char	*ext;

	ext = ft_strrchr(filename, '.');
	if (ext)
		if (ft_strncmp(ext, ".cub", 5) == CMP_FOUND)
			return (TRUE);
	return (FALSE);
}
