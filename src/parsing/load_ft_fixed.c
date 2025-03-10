/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_ft_fixed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:14:15 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/10 17:41:27 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

void    strip_map(char ***map_addr)
{
    ssize_t last_line;
    char **map = *map_addr;

    if (map == NULL)
        return ;
    last_line = ft_tablen(map);
    while (last_line && is_blank_line(map[--last_line]))
    {
        free(map[last_line]);
        map[last_line] = NULL;
    }
    if (last_line == 0)
    {
        free(map);
        *map_addr = NULL;
    }
}

int smallest_blank_gap_at_left_side(char **map)
{
    int smallest_gap = INT_MAX;
    int i;

    if (!map)
        return (-1);
    while (*map)
    {
        i = 0;
        while ((*map)[i] == ' ')
            i++;
        if (i < smallest_gap)
            smallest_gap = i;
        map++;
    }
    return (smallest_gap);
}

void trim_map(char ***map_addr)
{
    int smallest_gap;
    char **map;
    char *line;

    map = *map_addr;
    strip_map(map_addr);
    smallest_gap = smallest_blank_gap_at_left_side(map);
    while (*map)
    {
        line = *map;
        while (line[smallest_gap])
        {
            *line = line[smallest_gap];
            line++;
        }
        map++;
    }
}

void set_width_and_lenght(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (game->map.tab[i])
    {
        j = 0;
        while (game->map.tab[i][j])
            j++;
        if (j > game->map.width)
            game->map.width = j;
        i++;
    }
    game->map.height = i;
}

char	*load_map(t_game *game, char *line)
{
	if (game->map.tab)
		clean_exit(game, "[map] Error: Multiple maps", ERR_MULTIPLE_MAPS);
	else
		game->map.tab = get_map(game, game->fd, &line);
    //trim_map(&game->map.tab);
    set_width_and_lenght(game);
	return (line);
}

void	invalid_line(t_game *game, char *line)
{
	if (line)
		free(line);
	line = NULL;
	printf("error: %s\n", line);
	clean_exit(game, "Error: Invalid line", ERR_INVALID_LINE);
}

int	load_texture(t_game *game, int ind, char *line)
{
	char						*filename;

	if (game->textures.f_names[ind])
		clean_exit(game, "Error: Duplicated texture", ERR_LOADING_TEXTURE);
	filename = ft_get_next_wd(line, ' ');
	if (!filename)
		clean_exit(game, "Error: No texture filename", ERR_LOADING_TEXTURE);
	game->textures.f_names[ind] = ft_strtrim(filename, " \t\n");
    game->textures.orientation[ind] = mlx_load_png(game->textures.f_names[ind]);
    if (!game->textures.orientation[ind])
    {
        printf("error: %s\n", game->textures.f_names[ind]);
        clean_exit(game, "Error: mlx_load_png failed, check filename", ERR_LOADING_TEXTURE);
    }
	return (OK);
}
