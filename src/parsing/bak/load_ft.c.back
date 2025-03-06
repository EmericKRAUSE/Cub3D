/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_3d_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:14:15 by ekrause           #+#    #+#             */
/*   Updated: 2025/02/23 00:05:17 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

char *load_map(t_game *game, char *line)
{
    if (game->map.tab)
        clean_exit(game, "[map] whould be in one block", ERR_MULTIPLE_MAPS);
    else
        game->map.tab = get_map(game, game->fd, &line);
    return (line);
}

void invalid_line(t_game *game, char *line)
{
    if (line)
        free(line);
    line = NULL;
    printf("error: %s\n", line);
    clean_exit(game, "Error: Invalid line", ERR_INVALID_LINE);
}

int load_texture(t_game *game, int ind, char *line)
{
    char *filename;

    if (game->textures.f_names[ind])
        clean_exit(game, "Error: Two files for the same texture", ERR_LOADING_TEXTURE);
    filename = ft_get_next_wd(line, ' ');
    if (!filename)
        clean_exit(game, "Error: Invalid texture filename", ERR_LOADING_TEXTURE);
    game->textures.f_names[ind] = ft_strtrim(filename, " \t\n");
    return (OK);
}
