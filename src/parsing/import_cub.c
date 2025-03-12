/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_cub_fixed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/12 11:29:41 by nidionis         ###   ########.fr       */
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
    {
        if (param_missing_but_map(game))
            printf("[process_line] WARNING: map should be the last param\n");
        *line = load_map(game, *line);
    }
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

int	is_cub_file(char *filename)
{
    char	*ext;

    ext = ft_strrchr(filename, '.');
    if (ext)
        if (ft_strncmp(ext, ".cub", 5) == CMP_FOUND)
            return (TRUE);
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
    //game->player.start_x = get_player_position(game->map.tab);
    return (TRUE);
}
