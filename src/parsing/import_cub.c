/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/02/18 21:07:40 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

int import_cub_file(t_game *game)
{
    char *line;

    line = get_next_line(game->fd);
    game->map.tab = NULL;
    while (line)
    {
        if (is_blank_line(line))
        {
            free(line);
            line = get_next_line(game->fd);
        }
        else if (is_map(line))
            line = load_map(game, line);
        else if (is_texture(game, line))
        {
            if (get_texture(game, line) == ERR_LOADING_TEXTURE)
                clean_exit(game, "[get_texture] something went wrong", ERR_TEXTURE);
            free(line);
            line = get_next_line(game->fd);
        }
        else if (is_color(line))
        {
            if (get_color(game, line) == ERR_LOADING_TEXTURE)
                clean_exit(game, "[get_color] something went wrong", ERR_COLOR);
            free(line);
            line = get_next_line(game->fd);
        }
        else
        {
            invalid_line(game, line);
        }
    }
    return (TRUE);
}

int is_cub_file(char *filename)
{
    char *ext;

    ext = ft_strrchr(filename, '.');
    if (ext)
        if (ft_strncmp(ext, ".cub", 5) == CMP_FOUND)
            return (TRUE);
    return (FALSE);
}
