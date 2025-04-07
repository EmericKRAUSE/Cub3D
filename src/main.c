/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/04/07 15:46:19 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

t_rgb	init_color(int r, int g, int b)
{
	t_rgb	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", false);
	if (DISPLAY_MODE == RENDER_2D)
		game->minimap_scale = 1;
	else if (DISPLAY_MODE == RENDER_3D)
		game->minimap_scale = 0.2;
	game->tile_size = WIN_WIDTH / 42;
	game->scaled_tile_size = game->tile_size * game->minimap_scale;
	game->minimap = mlx_new_image(game->mlx, WIN_WIDTH * game->minimap_scale, WIN_HEIGHT * game->minimap_scale);
	game->player.image = mlx_new_image(game->mlx, game->scaled_tile_size, game->scaled_tile_size);
	game->player.angle = 0;
	game->player.rotation_speed = 0.04;
	game->textures.ceiling = init_color(UNSET_COLOR, UNSET_COLOR, UNSET_COLOR);
	game->textures.floor = init_color(UNSET_COLOR, UNSET_COLOR, UNSET_COLOR);
	game->ray = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->player.move_dist = game->tile_size / 8;
}

void	update_launcher(t_game *game)
{
	if (game->launcher_frame == 0)
		game->rocket_launcher[6]->instances->enabled = false;
	else
		game->rocket_launcher[game->launcher_frame - 1]->instances->enabled = false;
	game->rocket_launcher[game->launcher_frame]->instances->enabled = true;
}

void	hook_time(void *param)
{
	t_game *game;
	
	game = (t_game *)param;
	if (!game->is_shooting)
		return;
	game->time++;
	if (game->time % 3 == 0)
	{
		game->time = 0;
		game->launcher_frame++;
		if (game->launcher_frame > 6)
		{
			game->launcher_frame = 0;
			game->is_shooting = false;
		}
		update_launcher(game);
	}
}
	
void	mouse_event(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		if (!game->is_shooting)
			game->is_shooting = true;
	}
	(void)mods;
}

int	main(int argc, char **argv)
{
	t_game	*game;
	t_point	pt_player;

	if (SENSIVITY < 1 || SENSIVITY > 10)
		return (1);
	game = ft_calloc(sizeof(t_game), 1);
	init_game(game);
	game->textures.door = mlx_load_png("textures/door.png");
	if (!game)
	{
		return (ERR_MALLOC);
	}
	parse_args(argc, argv, game);
	pt_player = get_player_position(game->map.tab);
	game->player.x = pt_player.x * game->tile_size + game->tile_size / 2;
	game->player.y = pt_player.y * game->tile_size + game->tile_size / 2;
	
	mlx_set_mouse_pos(game->mlx, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	if (DISPLAY_MODE == RENDER_2D)
		display_minimap(game);
	else if (DISPLAY_MODE == RENDER_3D)
	{
		display_3d_map(game);
		mlx_loop_hook(game->mlx, &hook_time, game);
		mlx_key_hook(game->mlx, on_space_press, game);
		mlx_mouse_hook(game->mlx, mouse_event, game);
		mlx_cursor_hook(game->mlx, on_cursor_move, game);
	}
	mlx_loop_hook(game->mlx, &movements, game);
	mlx_loop_hook(game->mlx, &update_ray, game);
	mlx_loop(game->mlx);
	clean_exit(game, NULL, 0);
}
