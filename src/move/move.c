/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:44:56 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/03 18:12:41 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

// Update the new_x and new_y variable depending on the player angle
void	move_player(t_game *game, float *new_x, float *new_y)
{
	float	move_x;
	float	move_y;

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

// Hook for the movement and rotation of the player
void	movements(void *param)
{
	t_game	*game;
	float	new_x;
	float	new_y;
	int		map_x;
	int		map_y;

	game = param;
	new_x = game->player.image->instances->x;
	new_y = game->player.image->instances->y;
	rotate_player(game);
	move_player(game, &new_x, &new_y);
	map_x = (int)new_x / game->tile_size;
	map_y = (int)new_y / game->tile_size;
	if (game->map.tab[map_y][map_x] != '1')
	{
		game->player.image->instances->x = roundf(new_x);
		game->player.image->instances->y = roundf(new_y);
	}
}
