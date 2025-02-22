/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_3d_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:14:15 by ekrause           #+#    #+#             */
/*   Updated: 2025/02/22 19:25:21 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

void	draw_rectangle(t_game *game, mlx_image_t *img, int x_pos, int y_pos, uint32_t color)
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
	mlx_image_to_window(game->mlx, img, x_pos, y_pos);
}

void display_3d_map(t_game *game)
{
	mlx_image_t *floor;
	mlx_image_t *ceiling;
	
	floor = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT / 2);
	ceiling = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT / 2);
	
	draw_rectangle(game, ceiling, 0, 0, HEX_BLACK);
	draw_rectangle(game, floor, 0, WIN_HEIGHT / 2, HEX_WHITE);

	mlx_image_to_window(game->mlx, ceiling, 0, 0);
	mlx_image_to_window(game->mlx, game->player.image,
						game->player.start_x * game->tile_size,
						game->player.start_y * game->tile_size);
}
