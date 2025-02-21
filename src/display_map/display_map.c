/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:19:25 by ekrause           #+#    #+#             */
/*   Updated: 2025/02/21 15:19:32 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

void draw_square(t_game game, mlx_image_t *img, uint32_t color, int x_position, int y_position)
{
	int x;
	int y;

	y = 0;
	while (y < game.tile_size)
	{
		x = 0;
		while (x < game.tile_size)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
	mlx_image_to_window(game.mlx, img, x_position, y_position);
}

void display_map(t_game game)
{
	int x;
	int y;

	y = 0;
	while (game.map.tab[y])
	{
		x = 0;
		while (game.map.tab[y][x])
		{
			if (game.map.tab[y][x] == '1')
				draw_square(game, game.wall, 0x800080FF, x * game.tile_size, y * game.tile_size);
			else
				draw_square(game, game.background, 0x000000FF, x * game.tile_size, y * game.tile_size);
			x++;
		}
		y++;
	}
	mlx_image_to_window(game.mlx, game.player.image, game.player.x * game.tile_size, game.player.y * game.tile_size);
}