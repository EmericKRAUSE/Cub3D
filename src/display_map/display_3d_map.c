/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_3d_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:14:15 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/14 20:07:35 by ekrause          ###   ########.fr       */
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
}
