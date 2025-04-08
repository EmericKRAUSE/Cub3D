/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/04/08 14:06:35 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

int	is_launcher_initialised(t_game *game)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (!game->rocket_launcher[i])
			return (0);
		i++;
	}
	return (1);
}

void	update_launcher(t_game *game)
{
	if (!is_launcher_initialised(game))
		return ;
	if (game->launcher_frame == 0)
		game->rocket_launcher[6]->instances->enabled = false;
	else
		game->rocket_launcher[game->launcher_frame - 1]->instances->enabled
			= false;
	game->rocket_launcher[game->launcher_frame]->instances->enabled = true;
}

void	hook_time(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (!game->is_shooting)
		return ;
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

void	mouse_event(mouse_key_t button, action_t action, modifier_key_t mods,
	void *param)
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

	game = ft_calloc(sizeof(t_game), 1);
	init_game(game);
	parse_args(argc, argv, game);
	if (!game)
		return (ERR_MALLOC);
	init_player_pos(game);
	init_mouse(game);
	display_minimap(game);
	if (DISPLAY_MODE == RENDER_3D)
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
