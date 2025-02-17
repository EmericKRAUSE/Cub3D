#include "../../include/include.h"

void move(void *param)
{
	t_game *game;
	float move_x;
	float move_y;
	float new_x;
	float new_y;

	game = param;
	move_x = cos(game->player.angle);
	move_y = sin(game->player.angle);
	new_x = game->player.image->instances->x;
	new_y = game->player.image->instances->y;

	// Appliquer la rotation AVANT le déplacement
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		game->player.angle -= game->player.rotation_speed;
		if (game->player.angle > 2 * M_PI)
			game->player.angle -= 2 * M_PI;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		game->player.angle += game->player.rotation_speed;
		if (game->player.angle < 0)
			game->player.angle += 2 * M_PI;
	}
	// Recalculer move_x et move_y APRÈS la rotation
	move_x = cos(game->player.angle);
	move_y = sin(game->player.angle);

	// Appliquer déplacement
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		new_x += roundf(move_x * game->player.move_dist);
		new_y += roundf(move_y * game->player.move_dist);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		new_x -= roundf(move_x * game->player.move_dist);
		new_y -= roundf(move_y * game->player.move_dist);
	}

	// Vérifier collision AVANT de modifier la position
	if (game->map.map[(int)new_y / game->tile_size][(int)new_x / game->tile_size] != '1')
	{
		game->player.image->instances->x = new_x;
		game->player.image->instances->y = new_y;
	}
}
