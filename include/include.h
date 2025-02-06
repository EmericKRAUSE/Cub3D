#ifndef INCLUDE_H
# define INCLUDE_H

#include "../MLX42/include/MLX42/MLX42.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define WIN_WIDTH 1980
#define WIN_HEIGHT 1080

typedef struct game
{
	mlx_t		*mlx;
	mlx_image_t	*player;
}	t_game;

#endif