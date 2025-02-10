#ifndef INCLUDE_H
# define INCLUDE_H

#include "../MLX42/include/MLX42/MLX42.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define WIN_WIDTH 1980
#define WIN_HEIGHT 1080

#define PIXELS 32

// ####################
// Structures
typedef struct map
{
	char	**map;
	int		x;
	int		y;
}	t_map;

typedef struct game
{
	mlx_t		*mlx;
	t_map		map;
	mlx_image_t	*player;
	mlx_image_t *wall;
	mlx_image_t	*background;
	int			movement_distance;
	float		diagonal_factor;
}	t_game;

// ####################
// Prototypes
void	init_game(t_game* game);
int		map_parser(t_map *map, char *filename);
void	free_map(t_map *map);

#endif