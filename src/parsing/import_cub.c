/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/04/10 12:06:34 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

char	*free_and_get_line(char *line, int fd)
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

int	setmap(t_game *game, t_map *map_s)
{
	char	**map;

	map = map_s->tab;
	map_s->height = tab_len(map);
	map_s->width = ft_strlen(map[0]);
	if (map_s->height <= 0 || map_s->width <= 0 || map_s->height > map_s->width)
		clean_exit(game, "[setmap] too weird for me", ERR_INVALID_MAP);
	if (map_s->height > map_s->width)
	{
		printf("width = %i, height = %i\n", map_s->width, map_s->height);
		print_tab(map_s->tab);
		clean_exit(game, "[setmap] width < height", ERR_INVALID_MAP);
	}
	if (map_s->height > WIN_HEIGHT || map_s->width > WIN_WIDTH)
		clean_exit(game, "[setmap] too big for me", ERR_INVALID_MAP);
	if (map_s->height > HEIGH_MAX || map_s->width > WIDTH_MAX)
		clean_exit(game, "[setmap] too big for me", ERR_INVALID_MAP);
	return (TRUE);
}

// possible to use
// surround_map(game, &game->map.tab, SURROUNDING_CHAR);
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
	setmap(game, &game->map);
	return (TRUE);
}
