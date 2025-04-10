/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_cursor_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:37:54 by ekrause           #+#    #+#             */
/*   Updated: 2025/04/10 12:30:09 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

void	on_cursor_move(double xpos, double ypos, void *param)
{
	t_game	*game;
	double	x_travel;
	double	sens;

	game = param;
	if (game->mouse_hook)
	{
		return ;
	}
	sens = (SENSIVITY / 10000);
	x_travel = xpos - WIN_WIDTH / 2;
	game->player.angle += x_travel * sens;
	if (game->player.angle > 2 * M_PI)
		game->player.angle -= 2 * M_PI;
	else if (game->player.angle < 0)
		game->player.angle += 2 * M_PI;
	mlx_set_mouse_pos(game->mlx, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	(void)ypos;
}
