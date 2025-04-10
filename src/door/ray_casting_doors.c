/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_doors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 16:08:20 by ekrause           #+#    #+#             */
/*   Updated: 2025/04/01 19:40:53 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

// Return true if the position given in px is located in a wall or is out of map
static int	is_door_hit(t_game *game, float pos_x, float pos_y)
{
	char	**map_tab;
	int		map_width;
	int		map_height;
	t_point	map;

	map_tab = game->map.tab;
	map_width = game->map.width;
	map_height = game->map.height;
	map.x = pos_x / game->tile_size;
	map.y = pos_y / game->tile_size;
	if (pos_x <= 0 || pos_y <= 0)
		return (1);
	if (map.x < 0 || map.x >= map_width || map.y < 0 || map.y >= map_height)
		return (1);
	return (map_tab[map.y][map.x] == '1' || map_tab[map.y][map.x] == 'D'
		|| map_tab[map.y][map.x] == 'd');
}

/* Set nex_x and step_x values for the find_vertical_inter function
depending on the angle */
static void	d_set_vertical_values(t_game *game, float angle, float *next_x,
		float *step_x)
{
	int	tile_size;
	int	player_x;

	tile_size = game->tile_size;
	player_x = game->player.x;
	if (cos(angle) > 0)
	{
		*next_x = floor(player_x / tile_size) * tile_size + tile_size;
		*step_x = tile_size;
	}
	else
	{
		*next_x = floor(player_x / tile_size) * tile_size - 0.001;
		*step_x = -tile_size;
	}
}

/* Set nex_y and step_y values for the fond_horizontal_inter function
depending on the angle */
static void	d_set_horizontal_values(t_game *game, float angle, float *next_y,
		float *step_y)
{
	int	tile_size;
	int	player_y;

	tile_size = game->tile_size;
	player_y = game->player.y;
	if (sin(angle) > 0)
	{
		*next_y = floor(player_y / tile_size) * tile_size + tile_size;
		*step_y = tile_size;
	}
	else
	{
		*next_y = floor(player_y / tile_size) * tile_size - 0.001;
		*step_y = -tile_size;
	}
}

/* Calculates the trajectory of the ray at each vertical intersection
until it hits a wall then return the distance using pythagoras */
float	d_find_vertical_inter(t_game *game, float angle)
{
	t_point		player;
	t_fpoint	step;
	t_fpoint	next;

	d_set_vertical_values(game, angle, &next.x, &step.x);
	player.x = game->player.x;
	player.y = game->player.y;
	next.y = player.y + (next.x - player.x) * tan(angle);
	step.y = step.x * tan(angle);
	while (1)
	{
		if (is_door_hit(game, next.x, next.y))
			break ;
		next.x += step.x;
		next.y += step.y;
	}
	return (sqrt(pow(next.x - player.x, 2) + pow(next.y - player.y, 2)));
}

/* Calculates the trajectory of the ray at each horizontal intersection
until it hits a wall then return the distance using pythagoras */
float	d_find_horizontal_inter(t_game *game, float angle)
{
	t_point		player;
	t_fpoint	next;
	t_fpoint	step;

	d_set_horizontal_values(game, angle, &next.y, &step.y);
	player.x = game->player.x;
	player.y = game->player.y;
	next.x = player.x + (next.y - player.y) / tan(angle);
	step.x = step.y / tan(angle);
	while (1)
	{
		if (is_door_hit(game, next.x, next.y))
			break ;
		next.x += step.x;
		next.y += step.y;
	}
	return (sqrt(pow(next.x - player.x, 2) + pow(next.y - player.y, 2)));
}
