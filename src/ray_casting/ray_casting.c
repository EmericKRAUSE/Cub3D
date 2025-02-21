/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:48:38 by ekrause           #+#    #+#             */
/*   Updated: 2025/02/21 16:59:36 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

// Return true if the position given in px is located in a wall
static int	is_wall_hit(t_game *game, float ray_x, float ray_y)
{
	return (game->map.tab[(int)(ray_y / game->tile_size)]
			[(int)(ray_x / game->tile_size)] == '1');
}

// Cast a single ray
static void	cast_ray(t_game *game, float ray_angle)
{
	float	ray_x;
	float	ray_y;
	float	dx;
	float	dy;

	ray_x = game->player.image->instances->x;
	ray_y = game->player.image->instances->y;
	dx = cos(ray_angle);
	dy = sin(ray_angle);
	while (1)
	{
		ray_x += dx;
		ray_y += dy;
		if (is_wall_hit(game, ray_x, ray_y))
			break ;
		mlx_put_pixel(game->ray, (int)ray_x, (int)ray_y, COLOR_RAY);
	}
}

// Cast rays depending on: the player angle, the FOV and the the window's width
void	ray_casting(t_game *game)
{
	int		i;
	float	start_angle;
	float	step_angle;
	float	ray_angle;

	i = 0;
	start_angle = game->player.angle - FOV_RAD / 2;
	step_angle = FOV_RAD / WIN_WIDTH;
	if (game->ray)
		mlx_delete_image(game->mlx, game->ray);
	game->ray = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->ray)
		return ;
	while (i < WIN_WIDTH)
	{
		ray_angle = start_angle + i * step_angle;
		cast_ray(game, ray_angle);
		i++;
	}
	mlx_image_to_window(game->mlx, game->ray, 0, 0);
}
