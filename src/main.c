/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/17 16:35:22 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

void	draw_square(t_game game, mlx_image_t *img, uint32_t color,
		int x_position, int y_position)
{
	int	x;
	int	y;

	y = 0;
	while (y < game.tile_size)
	{
		x = 0;
		while (x < game.tile_size)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
	mlx_image_to_window(game.mlx, img, x_position, y_position);
}

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
	game->textures.ceiling = init_color(UNSET_COLOR, UNSET_COLOR, UNSET_COLOR);
	game->textures.floor = init_color(UNSET_COLOR, UNSET_COLOR, UNSET_COLOR);
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", false);
	game->tile_size = 64;
	game->ray = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->player.image = mlx_new_image(game->mlx, 1, 1);
	game->player.angle = 0;
	game->player.rotation_speed = 0.04;
	game->wall = mlx_new_image(game->mlx, game->tile_size, game->tile_size);
	game->background = mlx_new_image(game->mlx, game->tile_size,
			game->tile_size);
	game->player.move_dist = game->tile_size / 8;
}

void	mouse_event(mouse_key_t button, action_t action, modifier_key_t mods,
		void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (button == MLX_MOUSE_BUTTON_LEFT)
	{
		if (action == MLX_PRESS)
			printf("Tir ! 🔫\n");
	}
	(void)game;
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
	if (!game)
	{
		return (ERR_MALLOC);
	}
	parse_args(argc, argv, game);
	pt_player = get_player_position(game->map.tab);
	game->player.start_x = pt_player.x;
	game->player.start_y = pt_player.y;
	mlx_set_mouse_pos(game->mlx, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	if (DISPLAY_MODE == RENDER_2D)
		display_map(game);
	else if (DISPLAY_MODE == RENDER_3D)
		display_3d_map(game);
	mlx_loop_hook(game->mlx, &movements, game);
	mlx_loop_hook(game->mlx, &update_ray, game);
	mlx_cursor_hook(game->mlx, on_cursor_move, game);
	mlx_mouse_hook(game->mlx, mouse_event, game);
	mlx_loop(game->mlx);
	clean_exit(game, NULL, 0);
}
