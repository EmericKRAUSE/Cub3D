/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_nico_fixed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/06 16:53:51 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

int	open_file(t_game *game, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		clean_exit(game, "Error: File not found", ERR_OPENFILE);
	return (fd);
}

void	print_game(t_game *game)
{
	//printf("fd:																				 %d\n", game->fd);
	printf("map:\n");																							
	print_tab(game->map.tab);																					
	printf("\n");																								
	printf("north:														 %s\n", game->textures.f_names[NORTH]);
	printf("south:														 %s\n", game->textures.f_names[SOUTH]);
	printf("west:															 %s\n", game->textures.f_names[WEST]);
	printf("east:															 %s\n", game->textures.f_names[EAST]);
	printf("floor:		 %d %d %d\n", game->textures.floor.r, game->textures.floor.g, game->textures.floor.b);
	printf("ceiling: %d %d %d\n", game->textures.ceiling.r, game->textures.ceiling.g, game->textures.ceiling.b);

}

int	parse_args(int argc, char **argv, t_game *game)
{
	t_textures *textures;
	if (argc != 2)
		clean_exit(NULL, "Error: Argument must be 1", ERR_NBARGS);
	if (!is_cub_file(argv[1]))
		clean_exit(NULL, "Error: File must be .cub", ERR_CUBEXT);
	game->fd = open_file(game, argv[1]);
	import_cub_file(game);
	print_game(game);																							
	(void)textures;																								

	return (OK);
}
