#ifndef INCLUDE_H
# define INCLUDE_H

#include "../MLX42/include/MLX42/MLX42.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

#define WIN_WIDTH 1980
#define WIN_HEIGHT 1080

// ####################
// Structures
typedef struct game
{
	mlx_t		*mlx;
	char		**map;
	mlx_image_t	*player;
	int			movement_distance;
	float		diagonal_factor;
}	t_game;

// ####################
// Prototypes
void	init_game(t_game* game);

#endif