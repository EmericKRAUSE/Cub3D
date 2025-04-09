/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_line_fixed.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/04/09 15:53:58 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

void	prepend_line(t_game *game, char ***map, char *line)
{
	char	**new_map;
	int		i;

	i = 0;
	new_map = ft_calloc(sizeof(char *), ft_tablen(*map) + 2);
	if (!new_map)
		clean_exit(game, "Error: malloc failed (ft_calloc)", ERR_MALLOC);
	new_map[0] = line;
	while ((*map)[++i - 1])
		new_map[i] = (*map)[i - 1];
	free(*map);
	*map = new_map;
}

void	add_top_bottom_wall(t_game *game, char ***map, char c)
{
	char	*line;
	char	**new_map;

	line = ft_calloc(sizeof(char), ft_strlen((*map)[0]) + 1);
	if (!line)
		clean_exit(game, "Error: add wall (ft_calloc)", ERR_MALLOC);
	ft_memset(line, c, ft_strlen((*map)[0]));
	new_map = append_tab(*map, line);
	if (!new_map)
		clean_exit(game, "Error: add wall (ft_calloc)", ERR_MALLOC);
	line = ft_strdup(line);
	if (!line)
		clean_exit(game, "Error: add wall (ft_calloc)", ERR_MALLOC);
	prepend_line(game, &new_map, line);
	*map = new_map;
}

void	add_right_left_wall(t_game *game, char ***map, char c)
{
	char	*line;
	int		i;

	i = 0;
	while ((*map)[i])
	{
		line = ft_calloc(sizeof(char), ft_strlen((*map)[i]) + 3);
		if (!line)
			clean_exit(game, "Error: add wall (ft_calloc)", ERR_MALLOC);
		line[0] = c;
		ft_strlcpy(line + 1, (*map)[i], ft_strlen((*map)[i]) + 1);
		line[ft_strlen(line)] = c;
		free((*map)[i]);
		(*map)[i] = line;
		i++;
	}
}

void	surround_map(t_game *game, char ***map, char c)
{
	add_top_bottom_wall(game, map, c);
	add_right_left_wall(game, map, c);
}
