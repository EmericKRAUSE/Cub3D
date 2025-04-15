/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/04/15 15:24:04 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

// void	free_tab(char **map)
//{
//	char		**tmp;
//
//	tmp = map;
//	if (map)
//		while (*tmp)
//			free(*tmp++);
//	free(map);
//}

int	open_file(t_game *game, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd <= 0)
		clean_exit(game, "Error: cannot open file", ERR_OPENFILE, NULL);
	return (fd);
}

static t_rgb	init_color(int r, int g, int b)
{
	t_rgb	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

void	intit_game_parsing(t_game *game)
{
	game->map.tab = NULL;
	game->textures.ceiling = init_color(UNSET_COLOR, UNSET_COLOR, UNSET_COLOR);
	game->textures.floor = init_color(UNSET_COLOR, UNSET_COLOR, UNSET_COLOR);
	game->textures.door = mlx_load_png("textures/door.png");
	if (!game->textures.door)
		clean_exit(game, "Error: mlx_load_png failed, check filename",
			ERR_LOADING_TEXTURE, NULL);
}

int	parse_args(int argc, char **argv, t_game *game)
{
	if (argc != 2)
		clean_exit(game, "Error: Argument must be 1", ERR_NBARGS, NULL);
	if (!is_cub_file(argv[1]))
		clean_exit(game, "Error: File must be .cub", ERR_CUBEXT, NULL);
	game->fd = open_file(game, argv[1]);
	intit_game_parsing(game);
	import_cub_file(game);
	return (OK);
}
