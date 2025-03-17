/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/17 16:30:25 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

// void free_map(t_map *map)
//{
//    if (map)
//    {
//        if (map->tab)
//            free_tab(&map->tab);
//        free(map);
//    }
//}

int	ft_error(const char *msg, int exit_code)
{
	if (msg)
		printf("%s\n", msg);
	return (exit_code);
}

void	clean_get_next_line(t_game *game)
{
	char	*next_line;

	if (game->fd <= 0)
		return ;
	next_line = get_next_line(game->fd);
	while (next_line)
	{
		free(next_line);
		next_line = get_next_line(game->fd);
	}
	close(game->fd);
}

void	clean_exit(t_game *game, char *msg, int exit_code)
{
	int	i;

	if (game)
	{
		clean_get_next_line(game);
		ft_free_split(&game->map.tab);
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
