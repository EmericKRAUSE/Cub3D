/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:24:40 by ekrause           #+#    #+#             */
/*   Updated: 2025/04/08 17:08:30 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

// Return true is the position given in px is located in a wall
int	is_wall(t_game *game, float x, float y)
{
	t_point	map;

	map.x = (int)(x / game->tile_size);
	map.y = (int)(y / game->tile_size);
	if (map.x < 0 || map.y < 0 || map.y >= game->map.height
		|| map.x >= game->map.width)
		return (1);
	return (game->map.tab[map.y][map.x] == '1'
		|| game->map.tab[map.y][map.x] == 'D');
}

// Return true if the player is colliding with a wall using a hitbox
int	is_colliding(t_game *game, float new_x, float new_y)
{
	float	hit_box;

	hit_box = game->tile_size * 0.2;
	if (is_wall(game, new_x - hit_box, new_y - hit_box) || is_wall(game, new_x
			+ hit_box, new_y - hit_box) || is_wall(game, new_x - hit_box, new_y
			+ hit_box) || is_wall(game, new_x + hit_box, new_y + hit_box))
		return (1);
	return (0);
}
