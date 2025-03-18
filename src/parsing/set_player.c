/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/12 11:26:04 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

t_point	get_player_position(char **map)
{
	t_point	pos_player;

	pos_player.x = 0;
	pos_player.y = 0;
	while (map[pos_player.y])
	{
		pos_player.x = 0;
		while (map[pos_player.y][pos_player.x])
		{
			if (ft_strchr("NSWE", map[pos_player.y][pos_player.x]))
				return (pos_player);
			pos_player.x++;
		}
		pos_player.y++;
	}
	return (pos_player);
}

int	one_player_only(char **map)
{
	t_point	pos_player;
	char	**map_copy;

	pos_player = get_player_position(map);
	if (map[pos_player.y] == NULL)
	{
		printf("[one_player_only] no player\n");
		return (FALSE);
	}
	map_copy = dup_tab(map);
	set_map_point(map_copy, pos_player, '0');
	pos_player = get_player_position(map_copy);
	ft_free_split(&map_copy);
	if (map[pos_player.y] == NULL)
		return (TRUE);
	printf("[one_player_only] more than one player\n");
	return (FALSE);
}
