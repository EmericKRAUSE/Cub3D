/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:14:15 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/28 16:04:10 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

char	*load_map(t_game *game, char *line)
{
	if (game->map.tab)
		clean_exit(game, "[map] Error: Multiple maps", ERR_MULTIPLE_MAPS);
	else
		game->map.tab = get_map(game, game->fd, &line);
	if (!game->map.tab)
		clean_exit(game, "[map] Error: Map not available", ERR_MULTIPLE_MAPS);
	trim_map(&game->map.tab);
	if (!game->map.tab)
		clean_exit(game, "[map] Error: Map not available", ERR_MULTIPLE_MAPS);
	set_width_and_lenght(game);
	ft_square_map(game, CHAR_BLANK_MAP);
	return (line);
}

void	invalid_line(t_game *game, char *line)
{
	printf("error: %s\n", line);
	if (line)
		free(line);
	line = NULL;
	clean_exit(game, "Error: Invalid line", ERR_INVALID_LINE);
}

int	load_texture(t_game *game, int ind, char *line)
{
	char	*filename;

	if (game->textures.f_names[ind])
		clean_exit(game, "Error: Duplicated texture", ERR_LOADING_TEXTURE);
	filename = ft_get_next_wd(line, ' ');
	if (!filename)
		clean_exit(game, "Error: No texture filename", ERR_LOADING_TEXTURE);
	game->textures.f_names[ind] = ft_strtrim(filename, " \t\n");
	game->textures.orientation[ind] = mlx_load_png(game->textures.f_names[ind]);
	if (!game->textures.orientation[ind])
	{
		printf("error: %s\n", game->textures.f_names[ind]);
		clean_exit(game, "Error: mlx_load_png failed, check filename",
			ERR_LOADING_TEXTURE);
	}
	return (OK);
}
