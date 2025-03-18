/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_3d_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:14:15 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/18 14:40:11 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

// Draw a rectangle of size x: WIN_WIDTH y: WIN_HEIGHT / 2
void	draw_rectangle(mlx_image_t *img, uint32_t color)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

// Draw a crosshair based on CROSSHAIR_SIZE and CROSSHAIR_THICKNESS
void	draw_crosshair(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	game->crosshair = mlx_new_image(game->mlx, CROSSHAIR_SIZE, CROSSHAIR_SIZE);
	while (y < CROSSHAIR_SIZE)
	{
		x = 0;
		while (x < CROSSHAIR_SIZE)
		{
			if (x >= CROSSHAIR_SIZE / 2 - CROSSHAIR_THICKNESS / 2
				&& x <= CROSSHAIR_SIZE / 2 + CROSSHAIR_THICKNESS / 2)
				mlx_put_pixel(game->crosshair, x, y, COLOR_CROSSHAIR);
			else if (y >= CROSSHAIR_SIZE / 2 - CROSSHAIR_THICKNESS / 2
				&& y <= CROSSHAIR_SIZE / 2 + CROSSHAIR_THICKNESS / 2)
				mlx_put_pixel(game->crosshair, x, y, COLOR_CROSSHAIR);
			x++;
		}
		y++;
	}
	mlx_image_to_window(game->mlx, game->crosshair,
		WIN_WIDTH / 2 - game->crosshair->width / 2,
		WIN_HEIGHT / 2 - game->crosshair->height / 2);
	game->crosshair->instances->z = 4;
}

// Draw a gun on the middle bottom of the screen
void	draw_gun(t_game *game)
{
	mlx_texture_t	*gun_texture;

	gun_texture = mlx_load_png("gun.png");
	if (!gun_texture)
		return ;
	game->gun = mlx_texture_to_image(game->mlx, gun_texture);
	if (!game->gun)
		return ;
	mlx_delete_texture(gun_texture);
	mlx_image_to_window(game->mlx, game->gun,
		WIN_WIDTH / 2 - (game->gun->width / 2),
		WIN_HEIGHT - game->gun->height);
	game->gun->instances->z = 3;
}

void	draw_launcher(t_game *game)
{
	mlx_texture_t	*launcher_texture[7];

	launcher_texture[0] = mlx_load_png("ROCKETLAUNCHER_0001.png");
	launcher_texture[1] = mlx_load_png("ROCKETLAUNCHER_0002.png");
	launcher_texture[2] = mlx_load_png("ROCKETLAUNCHER_0003.png");
	launcher_texture[3] = mlx_load_png("ROCKETLAUNCHER_0004.png");
	launcher_texture[4] = mlx_load_png("ROCKETLAUNCHER_0005.png");
	launcher_texture[5] = mlx_load_png("ROCKETLAUNCHER_0006.png");
	launcher_texture[6] = mlx_load_png("ROCKETLAUNCHER_0007.png");
	
	for (int i = 0; i < 7; i++)
	{
		game->rocket_launcher[i] = mlx_texture_to_image(game->mlx, launcher_texture[i]);
		mlx_delete_texture(launcher_texture[i]);
		mlx_resize_image(game->rocket_launcher[i], game->rocket_launcher[i]->width * 4, game->rocket_launcher[i]->height * 4);
		mlx_image_to_window(game->mlx, game->rocket_launcher[i],
							WIN_WIDTH / 2 - (game->rocket_launcher[i]->width / 2),
							WIN_HEIGHT - game->rocket_launcher[i]->height);
		game->rocket_launcher[i]->instances->enabled = false;
		game->rocket_launcher[i]->instances->z = 3;
	}
	game->rocket_launcher[0]->instances->enabled = true;
}

// Draw the ceiling and floor using draw_rectanlge function
void	draw_ceiling_and_floor(t_game *game)
{
	game->images.ceiling = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT / 2);
	game->images.floor = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT / 2);
	if (!game->images.ceiling || !game->images.floor)
		return ;
	draw_rectangle(game->images.ceiling, COLOR_CEILING);
	draw_rectangle(game->images.floor, COLOR_FLOOR);
	mlx_image_to_window(game->mlx, game->images.ceiling, 0, 0);
	mlx_image_to_window(game->mlx, game->images.floor, 0, WIN_HEIGHT / 2);
	game->images.ceiling->instances->z = 0;
	game->images.floor->instances->z = 0;
}

// Draw everything needed for the 3D
void	display_3d_map(t_game *game)
{
	draw_ceiling_and_floor(game);
	draw_launcher(game);
	draw_crosshair(game);
	mlx_image_to_window(game->mlx, game->player.image,
		game->player.start_x * game->tile_size,
		game->player.start_y * game->tile_size);
}
