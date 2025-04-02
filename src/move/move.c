/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:44:56 by ekrause           #+#    #+#             */
/*   Updated: 2025/04/02 16:58:17 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

// Update the new_x and new_y variable depending on the player angle
void	move_player(t_game *game, double *new_x, double *new_y)
{
	double	move_x;
	double	move_y;

	move_x = cos(game->player.angle);
	move_y = sin(game->player.angle);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		*new_x += move_x * game->player.move_dist;
		*new_y += move_y * game->player.move_dist;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		*new_x += -move_x * game->player.move_dist;
		*new_y += -move_y * game->player.move_dist;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		*new_x += move_y * game->player.move_dist;
		*new_y += -move_x * game->player.move_dist;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		*new_x += -move_y * game->player.move_dist;
		*new_y += move_x * game->player.move_dist;
	}
}

// Update the angle of the player (0 to 2PI)
void	rotate_player(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		game->player.angle -= game->player.rotation_speed;
		if (game->player.angle < 0)
			game->player.angle += 2 * M_PI;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		game->player.angle += game->player.rotation_speed;
		if (game->player.angle > 2 * M_PI)
			game->player.angle -= 2 * M_PI;
	}
}

int is_wall(t_game *game, float x, float y)
{
	int map_x = (int)(x / game->tile_size);
	int map_y = (int)(y / game->tile_size);

	// Vérifie si on sort des limites de la map
	if (map_x < 0 || map_y < 0 || map_y >= game->map.height || map_x >= game->map.width)
		return (1); // Hors des limites = mur
	return (game->map.tab[map_y][map_x] == '1' || game->map.tab[map_y][map_x] == 'D');
}

int is_colliding(t_game *game, float new_x, float new_y)
{
	float hit_box = 10;

	if (is_wall(game, new_x - hit_box, new_y - hit_box) ||
		is_wall(game, new_x + hit_box, new_y - hit_box) ||
		is_wall(game, new_x - hit_box, new_y + hit_box) ||
		is_wall(game, new_x + hit_box, new_y + hit_box))
		return (1);
	return (0);
}

// Apply the movement depending on the collision detection using a margin
void apply_movement_with_collision(t_game *game, float new_x, float new_y)
{
	int can_move_x = !is_colliding(game, new_x, game->player.y);
	int can_move_y = !is_colliding(game, game->player.x, new_y);

	// Appliquer uniquement si la direction est libre
	if (can_move_x)
		game->player.x = round(new_x);
	if (can_move_y)
		game->player.y = round(new_y);
	game->player.image->instances->x = game->player.x * game->minimap_scale;
	game->player.image->instances->y = game->player.y * game->minimap_scale;
	//printf("real_pos:  %d\t%d\nimage_pos: %d\t%d\n", game->player.x, game->player.y, game->player.image->instances->x, game->player.image->instances->y);
	// printf("real_tile_size: %d\nscaled_tile_size%d\n", game->tile_size, game->scaled_tile_size);
}

// Hook for the movement and rotation of the player
void	movements(void *param)
{
	t_game	*game;
	double	new_x;
	double	new_y;

	game = param;
	new_x = game->player.x;
	new_y = game->player.y;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		clean_exit(game, NULL, 0);
	rotate_player(game);
	move_player(game, &new_x, &new_y);
	apply_movement_with_collision(game, new_x, new_y);
}
