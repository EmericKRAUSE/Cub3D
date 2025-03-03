/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:48:38 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/03 18:12:30 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

// Calculate the distance of a ray using Pythagoras and store it into an array
static void	calculate_distance(t_game *game, float ray_x, float ray_y, int i)
{
	float	player_x;
	float	player_y;

	player_x = game->player.image->instances->x;
	player_y = game->player.image->instances->y;
	
	game->ray_distances[i] = sqrtf(powf(player_x - ray_x, 2) + powf(player_y - ray_y, 2)) / game->tile_size;
	if (game->ray_distances[i] < 1)
		game->ray_distances[i] = 1;
}

// Return true if the position given in px is located in a wall
static int	is_wall_hit(t_game *game, float ray_x, float ray_y)
{
	return (game->map.tab[(int)(ray_y / game->tile_size)]
			[(int)(ray_x / game->tile_size)] == '1');
}

// Draw a point at every intersection
static void	cast_ray(t_game *game, float ray_angle, int i)
{
	float	ray_x;
	float	ray_y;
	float	dx;
	float	dy;
	int		tile_size = game->tile_size;

	ray_x = game->player.image->instances->x;
	ray_y = game->player.image->instances->y;
	if (ray_angle >= 7 * M_PI / 4 && ray_angle < 2 * M_PI)
	{
		printf("7\n");
		dx = tile_size;
		dy = -tile_size * tan(2 * M_PI - ray_angle);
	}
	else if (ray_angle >= 3 * M_PI / 2 && ray_angle < 7 * M_PI / 4)
	{
		printf("6\n");
		dx = tile_size * tan(ray_angle - 3 * M_PI / 2);
		dy = -tile_size;
	}
	else if (ray_angle >= 5 * M_PI / 4 && ray_angle < 3 * M_PI / 2)
	{
		printf("5\n");
		dx = -tile_size * tan(3 * M_PI / 2 - ray_angle);
		dy = -tile_size;
	}
	else if (ray_angle >= M_PI && ray_angle < 5 * M_PI / 4)
	{
		printf("4\n");
		dx = -tile_size;
		dy = -tile_size * tan(ray_angle - M_PI);
	}
	else if (ray_angle >= 3 * M_PI / 4 && ray_angle < M_PI)
	{
		printf("3\n");
		dx = -tile_size;
		dy = tile_size * tan(M_PI - ray_angle);
	}
	else if (ray_angle >= M_PI / 2 && ray_angle < 3 * M_PI / 4)
	{
		printf("2\n");
		dx = -tile_size * tan(ray_angle - M_PI / 2);
		dy = tile_size;
	}
	else if (ray_angle >= M_PI / 4 && ray_angle < M_PI / 2)
	{
		printf("1\n");
		dx = tile_size * tan(M_PI / 2 - ray_angle);
		dy = tile_size;
	}
	else if (ray_angle >= 0 && ray_angle < M_PI / 4)
	{
		printf("0\n");
		dx = tile_size;	
		dy = tile_size * tan(ray_angle);
	}
	int j = 0;
	while (j < 4)
	{
		mlx_put_pixel(game->ray, (int)ray_x, (int)ray_y, COLOR_RAY);
		ray_x += dx;
		ray_y += dy;
		if (is_wall_hit(game, ray_x, ray_y))
		{
			calculate_distance(game, ray_x, ray_y, i);
			break ;
		}
		j++;
	}
}

void draw_world(t_game *game)
{
	int i;

	if (game->world)
		mlx_delete_image(game->mlx, game->world);
	game->world = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->ray)
		return;
	i = 0;

	while (i < WIN_WIDTH)
	{
		int column_height = WIN_HEIGHT / (game->ray_distances[i]);

		int start_y = (WIN_HEIGHT / 2) - (column_height / 2);
		int end_y = (WIN_HEIGHT / 2) + (column_height / 2);

		for (int y = start_y; y < end_y; y++)
		{
			mlx_put_pixel(game->world, i, y, HEX_WHITE);
		}

		i++;
	}

	mlx_image_to_window(game->mlx, game->world, 0, 0);
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
	(void)ray_angle;
	if (game->ray)
		mlx_delete_image(game->mlx, game->ray);
	game->ray = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->ray)
		return ;
	while (i < 1)
	{
		ray_angle = start_angle + i * step_angle;
		cast_ray(game, game->player.angle, i);
		i++;
	}
	if (DISPLAY_MODE == RENDER_2D)
		mlx_image_to_window(game->mlx, game->ray, 0, 0);
	else if (DISPLAY_MODE == RENDER_3D)
		draw_world(game);
}
