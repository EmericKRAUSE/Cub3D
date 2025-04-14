/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:10:00 by ekrause           #+#    #+#             */
/*   Updated: 2025/04/15 00:05:26 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

static void	init_mouse(t_game *game)
{
	mlx_set_mouse_pos(game->mlx, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	game->mouse_hook = FALSE;
}

static void	init_player_pos(t_game *game)
{
	t_point	pt_player;

	pt_player = get_player_position(game->map.tab);
	game->player.x = pt_player.x * game->map.tile_size
		+ game->map.tile_size / 2;
	game->player.y = pt_player.y * game->map.tile_size
		+ game->map.tile_size / 2;
}

void	init_game_after(t_game *game)
{
	game->map.tile_size = fmin(WIN_WIDTH / game->map.width, WIN_HEIGHT
			/ game->map.height);
	game->map.minimap_tile_size = 40;
	if (DISPLAY_MODE == RENDER_2D)
		game->map.minimap_scale = 1;
	else if (DISPLAY_MODE == RENDER_3D)
		game->map.minimap_scale = (float)game->map.minimap_tile_size
			/ (float)game->map.tile_size;
	game->player.image = mlx_new_image(game->mlx, game->map.minimap_tile_size,
			game->map.minimap_tile_size);
	game->player.move_dist = game->map.tile_size / 8;
	init_player_pos(game);
	init_mouse(game);
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", false);
	if (DISPLAY_MODE == RENDER_2D)
		game->map.minimap_scale = 1;
	else if (DISPLAY_MODE == RENDER_3D)
		game->map.minimap_scale = 0.5;
	game->minimap = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->player.rotation_speed = 0.04;
}
