/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:44:56 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/14 17:34:42 by ekrause          ###   ########.fr       */
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


void	on_cursor_move(double xpos, double ypos, void *param)
{
	t_game	*game;
	double	x_travel;
	double	sens;

	game = param;
	sens = (SENSIVITY / 10000);
	x_travel = xpos - X_CENTER;
	game->player.angle += x_travel * sens;
	
	if (game->player.angle > 2 * M_PI)
		game->player.angle -= 2 * M_PI;
	else if (game->player.angle < 0)
		game->player.angle += 2 * M_PI;
	
	mlx_set_mouse_pos(game->mlx, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	(void)ypos;
}

// Hook for the movement and rotation of the player
void	movements(void *param)
{
	t_game	*game;
	double	new_x;
	double	new_y;
	double	map_x;
	double	map_y;
	double	collision_margin;

	game = param;
	new_x = game->player.image->instances->x;
	new_y = game->player.image->instances->y;

	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		clean_exit(game, NULL, 0);
	rotate_player(game);
	move_player(game, &new_x, &new_y);
	collision_margin = game->tile_size * 0.1;
	if (new_x > game->player.image->instances->x)
		map_x = (new_x + collision_margin) / game->tile_size;
	else
		map_x = (new_x - collision_margin) / game->tile_size;
	if (new_y > game->player.image->instances->y)
		map_y = (new_y + collision_margin) / game->tile_size;
	else
		map_y = (new_y - collision_margin) / game->tile_size;
	
	if (game->map.tab[game->player.image->instances->y / game->tile_size][(int)map_x] != '1')
		game->player.image->instances->x = round(new_x);
	if (game->map.tab[(int)map_y][game->player.image->instances->x / game->tile_size] != '1')
		game->player.image->instances->y = round(new_y);

	// if (game->map.tab[(int)map_y][(int)map_x] != '1')
	// {
	// 	game->player.image->instances->x = round(new_x);
	// 	game->player.image->instances->y = round(new_y);
	// }
}
