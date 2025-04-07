/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_3d_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:14:15 by ekrause           #+#    #+#             */
/*   Updated: 2025/04/07 17:45:42 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

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
	game->crosshair->instances->z = 5;
}

void	draw_floor_and_ceiling(mlx_image_t *img)
{
	int			x;
	int			y;
	uint32_t	color;

	x = 0;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				color = COLOR_CEILING;
			else
				color = COLOR_FLOOR;
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_ceiling_and_floor(t_game *game)
{
	game->floor_and_ceiling = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->floor_and_ceiling)
		return ;
	draw_floor_and_ceiling(game->floor_and_ceiling);
	mlx_image_to_window(game->mlx, game->floor_and_ceiling, 0, 0);
	game->floor_and_ceiling->instances->z = 0;
}

// Draw everything needed for the 3D
void	display_3d_map(t_game *game)
{
	draw_ceiling_and_floor(game);
	draw_launcher(game);
	draw_crosshair(game);
}
