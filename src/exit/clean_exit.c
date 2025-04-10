/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/04/10 18:14:47 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

int	ft_error(const char *msg, int exit_code)
{
	if (msg)
		printf("%s\n", msg);
	return (exit_code);
}

void	free_textures_and_images(t_game *game)
{
	if (game->textures.orientation[0])
		mlx_delete_texture(game->textures.orientation[0]);
	if (game->textures.orientation[1])
		mlx_delete_texture(game->textures.orientation[1]);
	if (game->textures.orientation[2])
		mlx_delete_texture(game->textures.orientation[2]);
	if (game->textures.orientation[3])
		mlx_delete_texture(game->textures.orientation[3]);
	if (game->textures.door)
		mlx_delete_texture(game->textures.door);
}

void	clean_exit(t_game *game, char *msg, int exit_code)
{
	int	i;

	if (game)
	{
        clean_get_next_line(game);
		ft_free_split(&game->map.tab);
		free_textures_and_images(game);
		if (game->mlx)
			mlx_terminate(game->mlx);
		i = 0;
		while (i < 4)
		{
			if (game->textures.f_names[i])
				free(game->textures.f_names[i]);
			i++;
		}
		free(game);
	}
	exit(ft_error(msg, exit_code));
}
