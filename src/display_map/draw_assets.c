/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:34:56 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/24 16:51:41 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

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
	int				i;

	launcher_texture[0] = mlx_load_png("ROCKETLAUNCHER_0001.png");
	launcher_texture[1] = mlx_load_png("ROCKETLAUNCHER_0002.png");
	launcher_texture[2] = mlx_load_png("ROCKETLAUNCHER_0003.png");
	launcher_texture[3] = mlx_load_png("ROCKETLAUNCHER_0004.png");
	launcher_texture[4] = mlx_load_png("ROCKETLAUNCHER_0005.png");
	launcher_texture[5] = mlx_load_png("ROCKETLAUNCHER_0006.png");
	launcher_texture[6] = mlx_load_png("ROCKETLAUNCHER_0007.png");
	i = -1;
	while (++i < 7)
	{
		game->rocket_launcher[i] = mlx_texture_to_image(game->mlx,
				launcher_texture[i]);
		mlx_delete_texture(launcher_texture[i]);
		mlx_resize_image(game->rocket_launcher[i], game->rocket_launcher[i]
			->width * 4, game->rocket_launcher[i]->height * 4);
		mlx_image_to_window(game->mlx, game->rocket_launcher[i],
			WIN_WIDTH / 2 - (game->rocket_launcher[i]->width / 2),
			WIN_HEIGHT - game->rocket_launcher[i]->height);
		game->rocket_launcher[i]->instances->enabled = false;
		game->rocket_launcher[i]->instances->z = 3;
	}
	game->rocket_launcher[0]->instances->enabled = true;
}
