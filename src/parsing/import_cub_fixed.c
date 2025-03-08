/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_cub_fixed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/08 15:21:16 by nidionis         ###   ########.fr       */
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


int is_map_available(t_game *game)
{
    if (game->map.tab == NULL)
        return (FALSE);
    if (!one_player_only(game->map.tab))
        return (FALSE);
    //if (!is_map_closed(game))
    //    return (FALSE);
    return (TRUE);
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
