/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_ft_fixed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:14:15 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/11 14:28:29 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

void    strip_map(char ***map_addr)
{
    ssize_t last_line;
    char **map = *map_addr;

    if (map == NULL)
        return ;
    last_line = ft_tablen(map) - 1;
    while (last_line && is_blank_line(map[last_line]))
    {
        free(map[last_line]);
        map[last_line] = NULL;
		last_line--;
    }
    if (last_line <= 0)
    {
        free(map[last_line]);
        free(map);
        map= NULL;
    }
	*map_addr = map;
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

void shift_to_left(char ***map_addr)
{
    int smallest_gap;
    char **map;
    char *line;
	int		i;

    map = *map_addr;
    smallest_gap = smallest_blank_gap_at_left_side(map);
	i = 0;
    while (map[i])
    {
        line = map[i];
        while (line[smallest_gap])
        {
            *line = line[smallest_gap];
            line++;
        }
        *line = line[smallest_gap];
        i++;
    }
	*map_addr = map;
}

void trim_map(char ***map_addr)
{
    strip_map(map_addr);
	if (*map_addr)
		shift_to_left(map_addr);
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

char **square_malloc(int width, int height)
{
    int i;
    char **tab;

    i = 0;
    tab = ft_calloc(sizeof(char *), height);
    if (!tab)
        return (NULL);
    while (i < height)
    {
        tab[i] = ft_calloc(sizeof(char), width);
        if (!tab[i])
        {
            ft_free_split(&tab);
            return (NULL);
        }
        i++;
    }
    return (tab);
}

void ft_square_map(t_game *game, char c)
{
    size_t i;
    size_t j;
    char **map = game->map.tab;
    char **new_map;

    i = 0;
    new_map = square_malloc(game->map.width + 1, game->map.height + 1);
    if (!new_map)
        clean_exit(game, "Error: malloc failed (ft_square_map)", ERR_MALLOC);
    while (i < (size_t)game->map.height)
    {
        j = 0;
        while (j < (size_t)game->map.width)
        {
            new_map[i][j] = c;
            if (j <= ft_strlen(map[i]))
                new_map[i][j] = map[i][j];
            j++;
        }
        i++;
    }
    ft_free_split(&game->map.tab);
    game->map.tab = new_map;
}

char	*load_map(t_game *game, char *line)
{
	if (game->map.tab)
		clean_exit(game, "[map] Error: Multiple maps", ERR_MULTIPLE_MAPS);
	else
		game->map.tab = get_map(game, game->fd, &line);
	if (!game->map.tab)
		clean_exit(game, "[map] Error: Map not available", ERR_MULTIPLE_MAPS);
    trim_map(&game->map.tab);
	if (!game->map.tab)
		clean_exit(game, "[map] Error: Map not available", ERR_MULTIPLE_MAPS);
    set_width_and_lenght(game);
    //ft_square_map(game, CHAR_BLANK_MAP);
	//print_tab(game->map.tab);
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
