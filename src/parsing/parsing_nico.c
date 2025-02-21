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

int open_file(t_game *game, char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
        clean_exit(game, "Error: File not found", ERR_OPENFILE);
    return (fd);
}

int is_map(char *line)
{
    if (!line)
        return (FALSE);
    else
        while (*line)
            if (!ft_strchr(MAP_CHARS, *line))
                return (FALSE);
    return (TRUE);
}

int is_texture(t_game *game, char *line)
{
    char **texture_balise;
    int i;
    int found;

    texture_balise = ft_split(TEXTURES_BALISE, '/');
    found = FALSE;
    if (!texture_balise)
        clean_exit(game, "Error: malloc failed", ERR_MALLOC);
    i = 0;
    if (!line)
        return (FALSE);
    else
        while (texture_balise[i] && !found)
            if (ft_strncmp(line, texture_balise[i], ft_strlen(texture_balise[i])) == CMP_FOUND)
                found = TRUE;
    ft_free_split(&texture_balise);
    return (found);
}

int is_color(t_game *game, char *line);
int get_texture(t_game *game, char *line);
int get_color(t_game *game, char *line);

char **get_map(t_game *game, int fd, char **line_addr)
{
    char **map;
    char *line;

    map = NULL;
    line = *line_addr;
    if (!is_map(line))
        clean_exit(game, "[get_map] NOT A MAP", ERR_MULTIPLE_MAPS);
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
    *line_addr = line;
    return (map);
}

t_textures *impor_cub_file(t_game *game, int fd)
{
    char *line;
    char **map;

    line = get_next_line(fd);
    map = NULL;
    while (line)
    {
        if (is_map(line))
        {
            if (map)
                clean_exit(game, "[map] whould be in one block", ERR_MULTIPLE_MAPS);
            else
                map = get_map(game, fd, &line);
        }
        //if (is_texture(game, line))
        //    if (get_texture(game, line) == ERR_LOADING_TEXTURE)
        //        clean_exit(game, "[get_texture] something went wrong", ERR_TEXTURE);
        //if (is_color(game, line))
        //    if (get_color(game, line) == ERR_LOADING_TEXTURE)
        //        clean_exit(game, "[get_color] something went wrong", ERR_COLOR);
    }
    
    return (NULL);
}

int parse_args(int argc, char **argv, t_game *game)
{
    int fd;
    t_textures *textures;

    if (argc != 2)
        return (ft_error("Error: Argument must be 1", 1));
    fd = open_file(game, argv[1]);
    textures = impor_cub_file(game, fd);   
    (void)fd;
    (void)textures;
    return (0);
}