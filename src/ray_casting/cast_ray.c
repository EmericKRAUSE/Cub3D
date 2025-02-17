#include "../../include/include.h"

void cast_ray(t_game *game, float ray_x, float ray_y)
{
	float dx = cos(game->player.angle);
	float dy = sin(game->player.angle);

	while (1)
	{
		ray_x += dx;
		ray_y += dy;
		int map_x = (int)(ray_x / game->tile_size);
		int map_y = (int)(ray_y / game->tile_size);

		if (game->map.map[map_y][map_x] == '1')
			break;

		mlx_put_pixel(game->ray, (int)ray_x, (int)ray_y, 0xFFFF00FF);
	}
	mlx_image_to_window(game->mlx, game->ray, 0, 0);
}
