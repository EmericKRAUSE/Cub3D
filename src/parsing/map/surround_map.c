/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_line_fixed.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/10 13:53:44 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

void add_top_bottom_wall(t_game *game, char ***map, char c)
{
  char *line;
  char **new_map;
  int i;

  line = ft_calloc(sizeof(char), game->map.width + 1);
  if (!line)
    clean_exit(game, "Error: add wall (ft_calloc)", ERR_MALLOC);
  ft_memset(line, c, game->map.width);
  new_map = append_tab(*map, line);
  if (!new_map)
    clean_exit(game, "Error: add wall (ft_calloc)", ERR_MALLOC);
  line = ft_strdup(line);
  if (!line)
    clean_exit(game, "Error: add wall (ft_calloc)", ERR_MALLOC);
  new_map = ft_calloc(sizeof(char *), 2);
  new_map[0] = line;
  i = 0;
  while ((*map)[i++])
    new_map[i] = (*map)[i - 1];
  free(*map);
  *map = new_map;
}

void surround_map(t_game *game, char ***map, char c)
{
  add_top_bottom_wall(game, map, c);
}
