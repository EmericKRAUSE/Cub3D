/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:34:56 by ekrause           #+#    #+#             */
/*   Updated: 2025/04/08 14:20:06 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

static void	init_launcher_texture(mlx_texture_t *launcher_texture[])
{
	launcher_texture[0] = mlx_load_png("img_assets/ROCKETLAUNCHER_00.png");
	launcher_texture[1] = mlx_load_png("img_assets/ROCKETLAUNCHER_01.png");
	launcher_texture[2] = mlx_load_png("img_assets/ROCKETLAUNCHER_02.png");
	launcher_texture[3] = mlx_load_png("img_assets/ROCKETLAUNCHER_03.png");
	launcher_texture[4] = mlx_load_png("img_assets/ROCKETLAUNCHER_04.png");
	launcher_texture[5] = mlx_load_png("img_assets/ROCKETLAUNCHER_05.png");
	launcher_texture[6] = mlx_load_png("img_assets/ROCKETLAUNCHER_06.png");
}

void	draw_launcher(t_game *game)
{
	mlx_texture_t	*launcher_texture[7];
	int				i;

	i = 0;
	init_launcher_texture(launcher_texture);
	while (i < 7)
	{
		if (!launcher_texture[i])
			return ;
		game->rocket_launcher[i] = mlx_texture_to_image(game->mlx,
				launcher_texture[i]);
		mlx_delete_texture(launcher_texture[i]);
		mlx_resize_image(game->rocket_launcher[i], game->rocket_launcher[i]
			->width * 4, game->rocket_launcher[i]->height * 4);
		mlx_image_to_window(game->mlx, game->rocket_launcher[i],
			WIN_WIDTH / 2 - (game->rocket_launcher[i]->width / 2),
			WIN_HEIGHT - game->rocket_launcher[i]->height);
		game->rocket_launcher[i]->instances->enabled = false;
		game->rocket_launcher[i]->instances->z = 4;
		i++;
	}
	game->rocket_launcher[0]->instances->enabled = true;
}
