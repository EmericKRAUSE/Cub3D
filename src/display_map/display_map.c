/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:19:25 by ekrause           #+#    #+#             */
/*   Updated: 2025/04/01 15:55:18 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

static void	set_point(t_point *point, int x, int y)
{
	point->x = x;
	point->y = y;
}

// Draw a square of size TILE_SIZE by TILE_SIZE
static void	draw_square(t_game *game, uint32_t color, t_point *point)
{
	int	x;
	int	y;

	y = 1;
	while (y < game->tile_size)
	{
		x = 1;
		while (x < game->tile_size)
		{
			mlx_put_pixel(game->minimap,  point->x + x, point->y + y, color);
			x++;
		}
		y++;
	}
}

// Draw a tile using the draw_square function depending on the character
void	draw_tile(t_game *game, char tile, int x, int y)
{
	t_point	point;

	set_point(&point, x * game->tile_size, y * game->tile_size);
	if (tile == '1')
		draw_square(game, COLOR_WALL, &point);
	else if (tile == 'D')
		draw_square(game, COLOR_DOOR, &point);
	else
		draw_square(game, COLOR_BACKGROUND, &point);
}

// Display the map
void	display_map(t_game *game)
{
	int		x;
	int		y;

	y = 0;
	while (game->map.tab[y])
	{
		x = 0;
		while (game->map.tab[y][x])
		{
			draw_tile(game, game->map.tab[y][x], x, y);
			x++;
		}
		y++;
	}
	mlx_image_to_window(game->mlx, game->minimap, 0, 0);
	mlx_image_to_window(game->mlx, game->player.image,
		game->player.start_x * game->tile_size + game->tile_size / 2,
		game->player.start_y * game->tile_size + game->tile_size / 2);
}
