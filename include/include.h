#ifndef INCLUDE_H
# define INCLUDE_H

#include "../MLX42/include/MLX42/MLX42.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define WIN_WIDTH 2560
#define WIN_HEIGHT (WIN_WIDTH * 9 / 16)
#define PI 3.14159265359

// ####################
// Structures
typedef struct player
{
	mlx_image_t	*image;
	int			x;
	int			y;
	int			move_dist;
	float		angle;
	float		rotation_speed;
}	t_player;

typedef struct map
{
	char	**map;
	int		x;
	int		y;
}	t_map;

typedef struct game
{
	mlx_t		*mlx;
	int			tile_size;
	mlx_image_t	*ray;
	t_map		map;
	t_player	player;
	mlx_image_t *wall;
	mlx_image_t	*background;
	float		diagonal_factor;
}	t_game;

// ####################
// Prototypes
void	init_game(t_game* game);
int		map_parser(t_map *map, char *filename);
void	free_map(t_map *map);

#endif