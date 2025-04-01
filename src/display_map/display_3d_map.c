/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_3d_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:14:15 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/31 12:55:18 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

// Draw a rectangle of size x: WIN_WIDTH y: WIN_HEIGHT / 2
void	draw_rectangle(mlx_image_t *img, uint32_t color)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

// Draw a crosshair based on CROSSHAIR_SIZE and CROSSHAIR_THICKNESS
void	draw_crosshair(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	game->crosshair = mlx_new_image(game->mlx, CROSSHAIR_SIZE, CROSSHAIR_SIZE);
	while (y < CROSSHAIR_SIZE)
	{
		x = 0;
		while (x < CROSSHAIR_SIZE)
		{
			if (x >= CROSSHAIR_SIZE / 2 - CROSSHAIR_THICKNESS / 2
				&& x <= CROSSHAIR_SIZE / 2 + CROSSHAIR_THICKNESS / 2)
				mlx_put_pixel(game->crosshair, x, y, COLOR_CROSSHAIR);
			else if (y >= CROSSHAIR_SIZE / 2 - CROSSHAIR_THICKNESS / 2
				&& y <= CROSSHAIR_SIZE / 2 + CROSSHAIR_THICKNESS / 2)
				mlx_put_pixel(game->crosshair, x, y, COLOR_CROSSHAIR);
			x++;
		}
		y++;
	}
	mlx_image_to_window(game->mlx, game->crosshair,
		WIN_WIDTH / 2 - game->crosshair->width / 2,
		WIN_HEIGHT / 2 - game->crosshair->height / 2);
	game->crosshair->instances->z = 4;
}

// Draw the ceiling and floor using draw_rectanlge function
void	draw_ceiling_and_floor(t_game *game)
{
	game->images.ceiling = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT / 2);
	game->images.floor = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT / 2);
	if (!game->images.ceiling || !game->images.floor)
		return ;
	draw_rectangle(game->images.ceiling, COLOR_CEILING);
	draw_rectangle(game->images.floor, COLOR_FLOOR);
	mlx_image_to_window(game->mlx, game->images.ceiling, 0, 0);
	mlx_image_to_window(game->mlx, game->images.floor, 0, WIN_HEIGHT / 2);
	game->images.ceiling->instances->z = 0;
	game->images.floor->instances->z = 0;
}

// Draw everything needed for the 3D
void	display_3d_map(t_game *game)
{
	draw_ceiling_and_floor(game);
	draw_launcher(game);
	draw_crosshair(game);
	mlx_image_to_window(game->mlx, game->player.image,
		game->player.start_x * game->tile_size,
		game->player.start_y * game->tile_size);
}
