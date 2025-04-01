/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_space_press.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:55:50 by ekrause           #+#    #+#             */
/*   Updated: 2025/04/01 19:40:23 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

void	open_and_close_door(t_game *game, float final_dist)
{
	t_point	map_hit;
	t_point	player;

	player.x = game->player.x;
	player.y = game->player.y;
	map_hit.x = (player.x + final_dist * cos(game->player.angle))
		/ game->tile_size;
	map_hit.y = (player.y + final_dist * sin(game->player.angle))
		/ game->tile_size;
	if (game->map.tab[map_hit.y][map_hit.x] == 'D')
		game->map.tab[map_hit.y][map_hit.x] = 'd';
	else if (game->map.tab[map_hit.y][map_hit.x] == 'd')
		game->map.tab[map_hit.y][map_hit.x] = 'D';
}

void	on_space_press(mlx_key_data_t keydata, void *param)
{
	t_game		*game;
	float		vertical_dist;
	float		horizontal_dist;
	float		final_dist;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_SPACE)
		&& keydata.action == MLX_PRESS)
	{
		vertical_dist = d_find_vertical_inter(game, game->player.angle);
		horizontal_dist = d_find_horizontal_inter(game, game->player.angle);
		if (vertical_dist < horizontal_dist)
			final_dist = vertical_dist;
		else
			final_dist = horizontal_dist;
		if (final_dist > 200 || final_dist < 1)
			return ;
		open_and_close_door(game, final_dist);
	}
}
