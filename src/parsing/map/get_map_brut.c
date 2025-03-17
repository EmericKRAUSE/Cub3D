/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_fixed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/10 21:32:16 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

char	**get_map(t_game *game, int fd, char **line_addr)
{
	char	**map;
	char	*line;

	map = NULL;
	line = *line_addr;
	if (!is_map(line))
		clean_exit(game, "[get_map] map invalid", ERR_INVALID_MAP);
	map = append_tab(map, line);
	if (map == NULL)
		clean_exit(game, "Error: malloc failed", ERR_MALLOC);
	line = get_next_line(fd);
	while (line && is_map(line))
	{
		map = append_tab(map, line);
		if (map == NULL)
			clean_exit(game, "Error: malloc failed", ERR_MALLOC);
		line = get_next_line(fd);
	}
	if (line && !is_map(line))
		*line_addr = line;
	else
		*line_addr = get_next_line(fd);
	return (map);
}
