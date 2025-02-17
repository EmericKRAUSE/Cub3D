#include "../../include/include.h"

void update_ray(void *param)
{
	t_game *game;

	game = param;
	mlx_delete_image(game->mlx, game->ray);
	game->ray = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	cast_ray(game, game->player.image->instances->x, game->player.image->instances->y);
}
