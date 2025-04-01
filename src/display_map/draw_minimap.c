/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 18:25:29 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/31 12:55:00 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

// static void set_point(t_point *point, int x, int y)
// {
// 	point->x = x;
// 	point->y = y;
// }

// // Draw a square of size TILE_SIZE by TILE_SIZE
// static void draw_square(t_game *game, mlx_image_t *img,
// 						uint32_t color, t_point *point)
// {
// 	int x;
// 	int y;

// 	y = 1;
// 	while (y < game->tile_size)
// 	{
// 		x = 1;
// 		while (x < game->tile_size)
// 		{
// 			mlx_put_pixel(img, x, y, color);
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_image_to_window(game->mlx, img, point->x, point->y);
// }

// // Draw a tile using the draw_square function depending on the character
// void draw_tile(t_game *game, char tile, int x, int y)
// {
// 	t_point point;

// 	set_point(&point, x * game->tile_size, y * game->tile_size);
// 	if (tile == '1')
// 		draw_square(game, game->wall, COLOR_WALL, &point);
// 	else if (tile == 'D')
// 		draw_square(game, game->door, COLOR_DOOR, &point);
// 	else
// 		draw_square(game, game->background, COLOR_BACKGROUND, &point);
// }

// // Display the map
// void display_map(t_game *game)
// {
// 	int x;
// 	int y;

// 	y = 0;
// 	while (game->map.tab[y])
// 	{
// 		x = 0;
// 		while (game->map.tab[y][x])
// 		{
// 			draw_tile(game, game->map.tab[y][x], x, y);
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_image_to_window(game->mlx, game->player.image,
// 						game->player.start_x * game->tile_size,
// 						game->player.start_y * game->tile_size);
// }

// void	draw_minimap(t_game *game)
// {
// 	// int i = 0;
// 	// int j;
// 	// while (i < game->minimap.height)
// 	// {
// 	// 	j = 0;
// 	// 	while (j < game->minimap.width)
// 	// 		mlx_put_pixel(game->minimap.image, j++, i, HEX_GREEN);
// 	// 	i++;
// 	// }
// 	mlx_image_to_window(game->mlx, game->minimap.image, 100, 100);
// 	//game->minimap.image->instances->z = 4;
// 	(void)game;
// 	printf("minimap!\n");
// }