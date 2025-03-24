/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_slice.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 21:09:50 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/24 21:36:59 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

uint32_t	get_color_pixel(mlx_texture_t *texture, int x, int y)
{
	int		index;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	if (x < 0 || x >= (int)texture->width || y < 0 || y >= (int)texture->height)
		return (0xFF000000);
	index = (y * texture->width + x) * texture->bytes_per_pixel;
	r = texture->pixels[index];
	g = texture->pixels[index + 1];
	b = texture->pixels[index + 2];
	a = texture->pixels[index + 3];
	return (r * 16777216 + g * 65536 + b * 256 + a);
}

void	draw_slice(t_game *game, int i, float ray_angle, t_slice slice)
{
	int		column_height;
	int		start_y;
	int		texture_x;
	int		texture_y;
	int		y;

	column_height = (WIN_HEIGHT / (slice.distance
				* cos(ray_angle - game->player.angle) / 100));
	start_y = (WIN_HEIGHT / 2) - (column_height / 2);
	texture_x = slice.hit_ratio * slice.texture->width;
	y = start_y;
	while (y < WIN_HEIGHT / 2 + column_height / 2)
	{
		texture_y = ((y - start_y) * slice.texture->height) / column_height;
		if (y >= 0 && y < WIN_HEIGHT)
			mlx_put_pixel(game->world, i, y,
				get_color_pixel(slice.texture, texture_x, texture_y));
		y++;
	}
}
