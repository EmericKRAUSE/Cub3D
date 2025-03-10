/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:48:38 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/06 19:18:06 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

// Calculate the distance of a ray using Pythagoras and store it into an array
// static void	calculate_distance(t_game *game, float ray_x, float ray_y, int i)
// {
// 	float	player_x;
// 	float	player_y;

// 	player_x = game->player.image->instances->x;
// 	player_y = game->player.image->instances->y;
	
// 	game->ray_distances[i] = sqrtf(powf(player_x - ray_x, 2) + powf(player_y - ray_y, 2)) / game->tile_size;
// 	if (game->ray_distances[i] < 1)
// 		game->ray_distances[i] = 1;
// }

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
	int tile_size;
	float delta_x;
	float delta_y;
	float step_x;
	float step_y;

	tile_size = game->tile_size;
	delta_x = game->player.image->instances->x;
	delta_y = game->player.image->instances->y;

	if (cos(angle) > 0) // Regarde a droite
	{
		//delta_x = floor(delta_x / tile_size) * tile_size;
		step_x = tile_size;
	}
	else // Regarde a gauche
	{
		//delta_x = floor(delta_x / tile_size) * tile_size + tile_size - 1;
		step_x= -tile_size - 1;
	}
	step_y = step_x * tan(angle);
	if (fabs(sin(angle)) < 0.0001) // Regard horizontal
		step_y = 0;
	if (fabs(cos(angle)) < 0.0001) // Regard vertical
	{
		step_y = tile_size;
		step_x = 0;
	}

	while (1)
	{
		delta_x += step_x;
		delta_y += step_y;
		if (is_out_of_map(game, roundf(delta_x), roundf(delta_y)) || is_wall_hit(game, delta_x, delta_y))
			break ;
		for (int j = 0; j < 5; j++)
			for (int k = 0; k < 5; k++)
				mlx_put_pixel(game->ray, roundf(delta_x) + k, roundf(delta_y) + j, COLOR_RAY);
	}
	return sqrt(pow(delta_x - game->player.image->instances->x, 2) + pow(delta_y - game->player.image->instances->y, 2));
}

float	find_horizontal_inter(t_game *game, float angle)
{
	int tile_size;
	float	delta_x;
	float	delta_y;
	float	step_x;
	float	step_y;
			
	tile_size = game->tile_size;
	delta_x = game->player.image->instances->x;
	delta_y = game->player.image->instances->y;

	for (int j = 0; j < 4; j++)
		for (int k = 0; k < 4; k++)
			mlx_put_pixel(game->ray, roundf(delta_x) + k, roundf(delta_y) + j, COLOR_PLAYER);

	if (sin(angle) > 0) // Regarde vers le bas
	{
		//delta_y = floor(delta_y / tile_size) * tile_size;
		step_y = tile_size;
	}
	else // Regarde vers le haut
	{
		//delta_y = floor(delta_y / tile_size) * tile_size + tile_size - 1;
		step_y = -tile_size - 1;
	}
	step_x = step_y / tan(angle);
	if (fabs(cos(angle)) < 0.0001) // Regard vertical
	{
		printf("vertical\n");
		step_x = 0;
	}
	if (fabs(sin(angle)) < 0.0001) // Regard horizontal
	{
		step_y = 0;
		step_x = tile_size;
	}

	while (1)
	{
		delta_x += step_x;
		delta_y += step_y;
		if (is_out_of_map(game, roundf(delta_x), roundf(delta_y)) || is_wall_hit(game, roundf(delta_x), roundf(delta_y)))
			break;
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++)
				mlx_put_pixel(game->ray, roundf(delta_x) + k, roundf(delta_y) + j, COLOR_RAY);
	}
	return sqrt(pow(delta_x - game->player.image->instances->x, 2) + pow(delta_y - game->player.image->instances->y, 2));
}

void draw_slice(t_game *game, float dist, int i, float ray_angle)
{
	// Correction pour le fish-eye effect
	//float corrected_dist = dist * cos(ray_angle); // Corrige la distance en fonction de l'angle
	(void)ray_angle;
	// Calcul de la hauteur de la colonne en fonction de la distance corrigée
	int column_height = (WIN_HEIGHT / (dist / 100));

	// Calcul de l'endroit où commencer et finir la colonne
	int start_y = (WIN_HEIGHT / 2) - (column_height / 2);
	int end_y = (WIN_HEIGHT / 2) + (column_height / 2);

	// Dessiner la colonne
	printf("start: %i\tend: %i\tcol: %i\tdist: %f\n", start_y, end_y, column_height, dist);
	for (int y = start_y; y < end_y; y++)
	{
		mlx_put_pixel(game->world, i, y, HEX_WHITE);
	}
}

// float	cast_test(t_game *game, float ray_angle)
// {
// 	float px = game->player.image->instances->x;
// 	float py = game->player.image->instances->y;
// 	float dx = cos(ray_angle);
// 	float dy = sin(ray_angle);

// 	while (1)
// 	{
// 		px += 1 * dx;
// 		py += 1 * dy;
// 		if (is_out_of_map(game, roundf(px), roundf(py)) || is_wall_hit(game, roundf(px), roundf(py)))
// 			break;
// 		mlx_put_pixel(game->ray, (int)px, (int)py, COLOR_RAY);
// 	}
// 	return sqrt(pow(px - game->player.image->instances->x, 2) + pow(py - game->player.image->instances->y, 2));
// }

// Draw a point at every intersection
static void	cast_ray(t_game *game, float ray_angle, int i)
{
	float	vertical_dist;
	float	horizontal_dist;

	vertical_dist = find_vertical_inter(game, ray_angle);
	horizontal_dist = find_horizontal_inter(game, ray_angle);

	if (vertical_dist < horizontal_dist)
	{
		draw_slice(game, vertical_dist, i, ray_angle);
	}
	else
	{
		draw_slice(game, horizontal_dist, i, ray_angle);
	}
	(void)i;
	(void)horizontal_dist;
	(void)vertical_dist;
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
		mlx_image_to_window(game->mlx, game->world, 0, 0);
}
