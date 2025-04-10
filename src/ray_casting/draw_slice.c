/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_slice.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 21:09:50 by ekrause           #+#    #+#             */
/*   Updated: 2025/04/10 12:10:11 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

// Get 4 pixels and return them into a uint32_t
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

// Draw a column of pixels
void	draw_slice(t_game *game, int i, float ray_angle, t_slice slice)
{
	int			h;
	int			start_y;
	t_point		texture;
	int			y;
	float		d_plane;

	d_plane = (WIN_WIDTH / 2) / tan((FOV * M_PI / 180) / 2);
	h = game->tile_size / \
	(slice.distance * cos(ray_angle - game->player.angle)) * d_plane;
	start_y = (WIN_HEIGHT / 2) - (h / 2);
	texture.x = slice.hit_ratio * slice.texture->width;
	y = start_y;
	while (y < WIN_HEIGHT / 2 + h / 2)
	{
		texture.y = ((y - start_y) * slice.texture->height) / h;
		if (y >= 0 && y < WIN_HEIGHT)
			mlx_put_pixel(game->world, i, y,
				get_color_pixel(slice.texture, texture.x, texture.y));
		y++;
	}
}
