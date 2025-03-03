/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:44:24 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/03 13:35:43 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

// static double pythagoras(int x, int y)
// {
// 	return (sqrt(x * x + y * y));
// }

// static float calculate_diagonal_factor(int distance)
// {
// 	return (distance / pythagoras(distance, distance));
// }

void	init_game(t_game *game)
{
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", false);
	game->tile_size = WIN_WIDTH / game->map.width;
	game->ray = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->player.image = mlx_new_image(game->mlx, 1, 1);
	game->player.angle = 0;
	game->player.rotation_speed = 0.05;
	game->wall = mlx_new_image(game->mlx, game->tile_size, game->tile_size);
	game->background = mlx_new_image(game->mlx, game->tile_size, game->tile_size);
	game->player.move_dist = game->tile_size / 5;
}
