/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:19:25 by ekrause           #+#    #+#             */
/*   Updated: 2025/04/07 15:38:14 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

// Draw a square of size TILE_SIZE by TILE_SIZE
static void	draw_square(t_game *game, uint32_t color, t_point *point)
{
	int	x;
	int	y;

	y = 1;
	while (y < game->scaled_tile_size)
	{
		x = 1;
		while (x < game->scaled_tile_size)
		{
			mlx_put_pixel(game->minimap, point->x + x, point->y + y, color);
			x++;
		}
		y++;
	}
}

static void	draw_player(t_game *game, uint32_t color)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->scaled_tile_size)
	{
		x = 0;
		while (x < game->scaled_tile_size)
		{
			mlx_put_pixel(game->player.image, x, y, color);
			x++;
		}
		y++;
	}
}

// Draw a tile using the draw_square function depending on the character
void	draw_tile(t_game *game, char tile, int x, int y)
{
	t_point	tile_pos;

	tile_pos.x = x * game->scaled_tile_size;
	tile_pos.y = y * game->scaled_tile_size;
	if (tile == '1')
		draw_square(game, COLOR_WALL, &tile_pos);
	else if (tile == 'D')
		draw_square(game, COLOR_DOOR, &tile_pos);
	else
		draw_square(game, COLOR_FLOOR, &tile_pos);
}

void	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT * game->minimap_scale)
	{
		x = 0;
		while (x < WIN_WIDTH * game->minimap_scale)
		{
			mlx_put_pixel(game->minimap, x, y, COLOR_BACKGROUND);
			x++;
		}
		y++;
	}
}

void	display_minimap(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	draw_background(game);
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
	draw_player(game, COLOR_PLAYER);
	mlx_image_to_window(game->mlx, game->player.image,
		game->player.x * game->minimap_scale,
		game->player.y * game->minimap_scale);
}
