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
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", false);
	game->tile_size = WIN_WIDTH / game->map.x;
	game->ray = mlx_new_image(game->mlx, 1, game->tile_size * 2);
	game->player.image = mlx_new_image(game->mlx, game->tile_size, game->tile_size);
	game->player.angle = 0;
	game->player.rotation_speed = 0.1;
	game->wall = mlx_new_image(game->mlx, game->tile_size, game->tile_size);
	game->background = mlx_new_image(game->mlx, game->tile_size, game->tile_size);
	game->player.move_dist = game->tile_size / 4;
	game->diagonal_factor = calculate_diagonal_factor(game->player.move_dist);
}