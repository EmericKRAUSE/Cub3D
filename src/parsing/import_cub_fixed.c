/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_cub_fixed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/06 17:22:36 by nidionis         ###   ########.fr       */
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

int	import_cub_file(t_game *game)
{
	char	*line;

	line = get_next_line(game->fd);
	game->map.tab = NULL;
	while (line)
		process_line(game, &line);
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
