/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:48:38 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/14 21:56:36 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

static int	is_out_of_map(t_game *game, float pos_x, float pos_y)
{
	int	map_width;
	int	map_height;
	int	pos_in_grid_x;
	int	pos_in_grid_y;

	map_width = game->map.width;
	map_height = game->map.height;
	pos_in_grid_x = pos_x / game->tile_size;
	pos_in_grid_y = pos_y / game->tile_size;
	return ((pos_in_grid_x < 0 || pos_in_grid_x >= map_width || pos_in_grid_y < 0 || pos_in_grid_y >= map_height));
}

// Return true if the position given in px is located in a wall
static int	is_wall_hit(t_game *game, float pos_x, float pos_y)
{
	char	**map;
	int		map_x;
	int		map_y;

	map = game->map.tab;
	map_x = pos_x / game->tile_size;
	map_y = pos_y / game->tile_size;
	return (map[map_y][map_x] == '1');
}

float find_vertical_inter(t_game *game, float angle)
{
	int tile_size = game->tile_size;
	int player_x = game->player.image->instances->x;
	int player_y = game->player.image->instances->y;
	float next_x, next_y;
	float step_x, step_y;

	if (cos(angle) > 0) // Regarde a droite
	{
		next_x = floor(player_x / tile_size) * tile_size + tile_size;
		step_x = tile_size;
	}
	else // Regarde a gauche
	{
		next_x = floor(player_x / tile_size) * tile_size - 0.001;
		step_x= -tile_size;
	}

	next_y = player_y + (next_x - player_x) * tan(angle);
	step_y = step_x * tan(angle);

	while (1)
	{
		if (is_out_of_map(game, next_x, next_y) || is_wall_hit(game, next_x, next_y))
			break ;
			
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++)
				mlx_put_pixel(game->ray, next_x + k, next_y + j, COLOR_RAY);

		next_x += step_x;
		next_y += step_y;
	}
	return sqrt(pow(next_x - player_x, 2) + pow(next_y - player_y, 2));
}

float find_horizontal_inter(t_game *game, float angle)
{
	int tile_size = game->tile_size;
	int player_x = game->player.image->instances->x;
	int player_y = game->player.image->instances->y;
	float next_x, next_y;
	float step_x, step_y;

	if (sin(angle) > 0) // Regarde vers le bas
	{
		next_y = floor(player_y / tile_size) * tile_size + tile_size;
		step_y = tile_size;
	}
	else // Regarde vers le haut
	{
		next_y = floor(player_y / tile_size) * tile_size - 0.001;
		step_y = -tile_size;
	}

	next_x = player_x + (next_y - player_y) / tan(angle);
	step_x = step_y / tan(angle);

	while (1)
	{
		if (is_out_of_map(game, next_x, next_y) || is_wall_hit(game, next_x, next_y))
			break;

		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++)
				mlx_put_pixel(game->ray, next_x + k, next_y + j, COLOR_RAY);

		next_x += step_x;
		next_y += step_y;
	}
	return sqrt(pow(next_x - player_x, 2) + pow(next_y - player_y, 2));
}

void draw_slice(t_game *game, float dist, int i, float ray_angle, int color)
{
	float corrected_dist = dist * cos(ray_angle - game->player.angle);

	int column_height = (WIN_HEIGHT / (corrected_dist / 100));
	int	max_column_height = WIN_HEIGHT;

	if (column_height > max_column_height)
		column_height = max_column_height;

	int start_y = (WIN_HEIGHT / 2) - (column_height / 2);
	int end_y = (WIN_HEIGHT / 2) + (column_height / 2);

	for (int y = start_y; y < end_y; y++)
	{
		mlx_put_pixel(game->world, i, y, color);
	}
}

// double	cast_test(t_game *game, float angle)
// {
// 	int		player_x, player_y;
// 	double	dx, dy;
// 	double	cx, sy;
	
// 	player_x = game->player.image->instances->x;
// 	player_y = game->player.image->instances->y;
// 	dx = player_x;
// 	dy = player_y;
// 	cx = cos(angle);
// 	sy = sin(angle);
	
// 	while (1)
// 	{
// 		if (is_out_of_map(game, dx, dy) || is_wall_hit(game, dx, dy))
// 			break;

// 		dx += cx * 1;
// 		dy += sy * 1;

// 		// for (int j = 0; j < 4; j++)
// 		// 	for (int k = 0; k < 4; k++)
// 				//mlx_put_pixel(game->ray, roundf(dx), roundf(dy), COLOR_RAY);
// 	}
// 	return sqrt(pow(dx - player_x, 2) + pow(dy - player_y, 2));
// }

// Draw a point at every intersection
static void	cast_ray(t_game *game, float ray_angle, int i)
{
	float		vertical_dist;
	float		horizontal_dist;
	float		final_dist;
	int			color;

	vertical_dist = find_vertical_inter(game, ray_angle);
	horizontal_dist = find_horizontal_inter(game, ray_angle);

	if (DISPLAY_MODE == RENDER_3D)
	{
		if (vertical_dist < horizontal_dist)
		{
			final_dist = vertical_dist;
			if (cos(ray_angle) > 0)
				color = COLOR_WALL_EAST;
			else
				color = COLOR_WALL_WEST;
		}
		else
		{
			final_dist = horizontal_dist;
			if (sin(ray_angle) > 0)
				color = COLOR_WALL_SOUTH;
			else
				color = COLOR_WALL_NORTH;
		}
		draw_slice(game, final_dist, i, ray_angle, color);
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
		
	if (game->world)
		mlx_delete_image(game->mlx, game->world);
	game->world = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->world)
		return ;

	while (i < WIN_WIDTH)
	{
		ray_angle = start_angle + i * step_angle;
		if (ray_angle > 2 * M_PI)
			ray_angle -= 2 * M_PI;
		else if (ray_angle < 0)
			ray_angle += 2 * M_PI;
		cast_ray(game, ray_angle, i);
		i++;
	}
	if (DISPLAY_MODE == RENDER_2D)
		mlx_image_to_window(game->mlx, game->ray, 0, 0);
	else if (DISPLAY_MODE == RENDER_3D)
	{
		mlx_image_to_window(game->mlx, game->world, 0, 0);
		game->world->instances->z = 1;
	}
}
