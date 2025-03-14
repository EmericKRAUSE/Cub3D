/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_3d_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:14:15 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/14 21:53:35 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

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

void	draw_crosshair(t_game *game, int width, int height)
{
	int	x;
	int	y = 0;
	game->crosshair = mlx_new_image(game->mlx, width, height);

	while(y < height)
	{
		x = 0;
		while (x < width)
		{
			if (x == width / 2 || y == height / 2)
			mlx_put_pixel(game->crosshair, x, y, COLOR_CROSSHAIR);
			x++;
		}
		y++;
	}
	mlx_image_to_window(game->mlx, game->crosshair, X_CENTER - game->crosshair->width / 2, Y_CENTER - game->crosshair->height / 2);
	game->crosshair->instances->z = 4;
}

void	draw_gun(t_game *game)
{
	mlx_texture_t	*gun_texture;
	mlx_image_t		*gun_image;
	
	gun_texture = mlx_load_png("gun.png");
	if (!gun_texture)
		return ;

	gun_image = mlx_texture_to_image(game->mlx, gun_texture);
	if (!gun_image)
		return ;

	mlx_image_to_window(game->mlx, gun_image, X_CENTER - (gun_image->width / 2), WIN_HEIGHT - gun_image->height);
	gun_image->instances->z = 3;
}

void display_3d_map(t_game *game)
{
	mlx_image_t *floor;
	mlx_image_t *ceiling;
	
	floor = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT / 2);
	ceiling = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT / 2);
	
	draw_rectangle(ceiling, COLOR_CEILING);
	draw_rectangle(floor, COLOR_FLOOR);

	mlx_image_to_window(game->mlx, ceiling, 0, 0);
	mlx_image_to_window(game->mlx, floor, 0, WIN_HEIGHT / 2);
	mlx_image_to_window(game->mlx, game->player.image,
						game->player.start_x * game->tile_size,
						game->player.start_y * game->tile_size);

	ceiling->instances->z = 0;
	floor->instances->z = 0;

	draw_gun(game);
	draw_crosshair(game, 21, 21);
}
