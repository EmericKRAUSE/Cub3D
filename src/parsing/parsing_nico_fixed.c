/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_nico_fixed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/08 14:43:12 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

void	free_tab(char **map)
{
	char		**tmp;

	tmp = map;
	if (map)
		while (*tmp)
			free(*tmp++);
	free(map);
}

int	open_file(t_game *game, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd <= 0)
		clean_exit(game, "Error: cannot open file", ERR_OPENFILE);
	return (fd);
}

int	parse_args(int argc, char **argv, t_game *game)
{
	if (argc != 2)
		clean_exit(NULL, "Error: Argument must be 1", ERR_NBARGS);
	if (!is_cub_file(argv[1]))
		clean_exit(NULL, "Error: File must be .cub", ERR_CUBEXT);
	game->fd = open_file(game, argv[1]);
	import_cub_file(game);
	return (OK);
}
