/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:34:18 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/28 17:35:48 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

int	prepare_world_image(t_game *game)
{
	if (game->world)
		mlx_delete_image(game->mlx, game->world);
	game->world = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->world)
		return (-1);
	return (1);
}

void	normalize_angle(float *angle)
{
	if (*angle > 2 * M_PI)
		*angle -= 2 * M_PI;
	else if (*angle < 0)
		*angle += 2 * M_PI;
}
