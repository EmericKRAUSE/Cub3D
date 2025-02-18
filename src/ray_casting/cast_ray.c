#include "../../include/include.h"

void cast_ray(t_game *game)
{
	int		i = 0;
	float start_angle = game->player.angle - FOV_RAD / 2;
	float	ray_angle;
	float step_angle = FOV_RAD / WIN_WIDTH;

	if (game->ray)
		mlx_delete_image(game->mlx, game->ray);
	game->ray = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->ray)
		return ;

	while(i < WIN_WIDTH)
	{
		ray_angle = start_angle + i * step_angle;
		float dx = cos(ray_angle);
		float dy = sin(ray_angle);
		float ray_x = game->player.image->instances->x;
		float ray_y = game->player.image->instances->y;
		while (1)
		{
			ray_x += dx;
			ray_y += dy;
			int map_x = (int)(ray_x / game->tile_size);
			int map_y = (int)(ray_y / game->tile_size);
	
			if (game->map.tab[map_y][map_x] == '1')
				break;
	
			mlx_put_pixel(game->ray, (int)ray_x, (int)ray_y, 0xFFFF00FF);
		}
		i++;
	}
	mlx_image_to_window(game->mlx, game->ray, 0, 0);
}
