#include "../../include/include.h"

static double pythagoras(int x, int y)
{
	return (sqrt(x * x + y * y));
}

static float calculate_diagonal_factor(int distance)
{
	return (distance / pythagoras(distance, distance));
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", true);
	game->player = mlx_new_image(game->mlx, PIXELS, PIXELS);
	game->wall = mlx_new_image(game->mlx, PIXELS, PIXELS);
	game->background = mlx_new_image(game->mlx, PIXELS, PIXELS);
	game->movement_distance = PIXELS / 10;
	game->diagonal_factor = calculate_diagonal_factor(game->movement_distance);
}