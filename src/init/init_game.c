/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:10:00 by ekrause           #+#    #+#             */
/*   Updated: 2025/04/10 12:33:47 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

static t_rgb	init_color(int r, int g, int b)
{
	t_rgb	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

static void	init_mouse(t_game *game)
{
	mlx_set_mouse_pos(game->mlx, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	game->mouse_hook = TRUE;
}

static void	init_player_pos(t_game *game)
{
	t_point	pt_player;

	pt_player = get_player_position(game->map.tab);
	game->player.x = pt_player.x * game->tile_size + game->tile_size / 2;
	game->player.y = pt_player.y * game->tile_size + game->tile_size / 2;
}

void	init_game_after(t_game *game)
{
	game->tile_size = fmin(WIN_WIDTH / game->map.width, WIN_HEIGHT
			/ game->map.height);
	game->scaled_tile_size = game->tile_size * game->minimap_scale;
	if (game->tile_size < WIN_WIDTH / MIN_TILE_SIZE)
	{
		game->scaled_tile_size = MIN_TILE_SIZE * game->minimap_scale;
	}
	game->player.image = mlx_new_image(game->mlx, game->scaled_tile_size,
			game->scaled_tile_size);
	game->player.move_dist = game->tile_size / 8;
	init_player_pos(game);
	init_mouse(game);
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", false);
	if (DISPLAY_MODE == RENDER_2D)
		game->minimap_scale = 1;
	else if (DISPLAY_MODE == RENDER_3D)
		game->minimap_scale = 0.2;
	game->minimap = mlx_new_image(game->mlx, WIN_WIDTH * game->minimap_scale,
			WIN_HEIGHT * game->minimap_scale);
	game->player.angle = 0;
	game->player.rotation_speed = 0.04;
	game->textures.ceiling = init_color(UNSET_COLOR, UNSET_COLOR, UNSET_COLOR);
	game->textures.floor = init_color(UNSET_COLOR, UNSET_COLOR, UNSET_COLOR);
	game->textures.door = mlx_load_png("textures/door.png");
}
