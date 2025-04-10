/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:44:56 by ekrause           #+#    #+#             */
/*   Updated: 2025/04/10 12:27:26 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

// Update the new_x and new_y variable depending on the player angle
static void	move_player(t_game *game, float *new_x, float *new_y)
{
	t_fpoint	move;

	move.x = cos(game->player.angle);
	move.y = sin(game->player.angle);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		*new_x += move.x * game->player.move_dist;
		*new_y += move.y * game->player.move_dist;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		*new_x += -move.x * game->player.move_dist;
		*new_y += -move.y * game->player.move_dist;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		*new_x += move.y * game->player.move_dist;
		*new_y += -move.x * game->player.move_dist;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		*new_x += -move.y * game->player.move_dist;
		*new_y += move.x * game->player.move_dist;
	}
}

// Update the angle of the player (0 to 2PI)
static void	rotate_player(t_game *game)
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

// Apply the movement depending on the collision detection using a hitbox
static void	apply_movement_with_collision(t_game *game, float new_x,
		float new_y)
{
	t_point	can_move;

	can_move.x = !is_colliding(game, new_x, game->player.y);
	can_move.y = !is_colliding(game, game->player.x, new_y);
	if (can_move.x)
		game->player.x = round(new_x);
	if (can_move.y)
		game->player.y = round(new_y);
	game->player.image->instances->x = game->player.x * game->minimap_scale;
	game->player.image->instances->y = game->player.y * game->minimap_scale;
}

// Hook for the movement and rotation of the player
void	movements(void *param)
{
	t_game	*game;
	float	new_x;
	float	new_y;

	game = param;
	new_x = game->player.x;
	new_y = game->player.y;
	if (mlx_is_key_down(game->mlx, MLX_KEY_M))
	{
		game->mouse_hook = !game->mouse_hook;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		clean_exit(game, NULL, 0);
	rotate_player(game);
	move_player(game, &new_x, &new_y);
	apply_movement_with_collision(game, new_x, new_y);
}
