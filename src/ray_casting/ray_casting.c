/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 20:48:38 by ekrause           #+#    #+#             */
/*   Updated: 2025/04/07 17:45:00 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

static int	is_door(t_game *game, t_fpoint hit)
{
	t_point	map;

	map.x = hit.x / game->tile_size;
	map.y = hit.y / game->tile_size;
	return (game->map.tab[map.y][map.x] == 'D');
}

static void	set_vertical_slice(t_game *game, t_slice *slice,
	float vertical_dist, float ray_angle)
{
	t_fpoint	hit;

	slice->distance = vertical_dist;
	hit.y = game->player.y + slice->distance * sin(ray_angle);
	hit.x = game->player.x + slice->distance * cos(ray_angle);
	if (cos(ray_angle) < 0)
		hit.x -= 0.001;
	else
		hit.x += 0.001;
	slice->hit_ratio = hit.y - floor(hit.y / game->tile_size) * game->tile_size;
	if (is_door(game, hit))
		slice->texture = game->textures.door;
	else if (cos(ray_angle) > 0)
		slice->texture = game->textures.orientation[WEST];
	else
		slice->texture = game->textures.orientation[EAST];
}

static void	set_horizontal_slice(t_game *game, t_slice *slice,
	float horizontal_dist, float ray_angle)
{
	t_fpoint	hit;

	slice->distance = horizontal_dist;
	hit.y = game->player.y + slice->distance * sin(ray_angle);
	hit.x = game->player.x + slice->distance * cos(ray_angle);
	if (sin(ray_angle) < 0)
		hit.y -= 0.001;
	else
		hit.y += 0.001;
	slice->hit_ratio = hit.x - floor(hit.x / game->tile_size) * game->tile_size;
	if (is_door(game, hit))
		slice->texture = game->textures.door;
	else if (sin(ray_angle) > 0)
		slice->texture = game->textures.orientation[NORTH];
	else
		slice->texture = game->textures.orientation[SOUTH];
}

// Draw a point at every intersection
static void	cast_ray(t_game *game, float ray_angle, int i)
{
	float			vertical_dist;
	float			horizontal_dist;
	t_slice			slice;

	vertical_dist = find_vertical_inter(game, ray_angle);
	horizontal_dist = find_horizontal_inter(game, ray_angle);
	if (DISPLAY_MODE == RENDER_3D)
	{
		if (vertical_dist < horizontal_dist)
			set_vertical_slice(game, &slice, vertical_dist, ray_angle);
		else
			set_horizontal_slice(game, &slice, horizontal_dist, ray_angle);
		slice.hit_ratio = slice.hit_ratio / game->tile_size;
		draw_slice(game, i, ray_angle, slice);
	}
}

// Cast rays depending on: the player angle, the FOV and the the window's width
void	ray_casting(t_game *game)
{
	int		i;
	float	fov_rad;
	float	start_angle;
	float	step_angle;
	float	ray_angle;

	i = 0;
	fov_rad = FOV * (M_PI / 180);
	start_angle = game->player.angle - fov_rad / 2;
	step_angle = fov_rad / WIN_WIDTH;
	if (!prepare_world_image(game))
		return ;
	while (i < WIN_WIDTH)
	{
		ray_angle = start_angle + i * step_angle;
		normalize_angle(&ray_angle);
		cast_ray(game, ray_angle, i);
		i++;
	}
	if (DISPLAY_MODE == RENDER_3D)
	{
		mlx_image_to_window(game->mlx, game->world, 0, 0);
		game->world->instances->z = 1;
	}
}
