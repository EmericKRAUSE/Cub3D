/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_nico.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/03 22:22:36 by nidionis         ###   ########.fr       */
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
            if (!ft_strchr(MAP_CHARS, *line++))
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
        *line_addr = NULL;
    print_tab(map);
    return (map);
}

int is_blank(char *line)
{
    if (line)
        while (*line)
            if (!ft_strchr(BLANK_CHAR, *line++))
                return (FALSE);
    return (TRUE);
}

void load_map(t_game *game, char *line, int fd)
{
    if (game->map.tab)
    {
        free(line);
        clean_exit(game, "[map] whould be in one block", ERR_MULTIPLE_MAPS);
    }
    else
        game->map.tab = get_map(game, fd, &line);
}

void invalid_line(t_game *game, char *line)
{
    if (line)
        free(line);
    line = NULL;
    clean_exit(game, "Error: Invalid line", ERR_INVALID_LINE);
}

int impor_cub_file(t_game *game, int fd)
{
    char *line;

    line = get_next_line(fd);
    game->map.tab = NULL;
    while (line)
    {
        if (is_map(line))
            load_map(game, line, fd);
        //if (is_texture(game, line))
        //    if (get_texture(game, line) == ERR_LOADING_TEXTURE)
        //        clean_exit(game, "[get_texture] something went wrong", ERR_TEXTURE);
        //if (is_color(game, line))
        //    if (get_color(game, line) == ERR_LOADING_TEXTURE)
        //        clean_exit(game, "[get_color] something went wrong", ERR_COLOR);
        else if (is_blank(line))
        {
            free(line);
            line = get_next_line(fd);
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

int parse_args(int argc, char **argv, t_game *game)
{
    int fd;
    t_textures *textures;

    if (argc != 2)
        clean_exit(NULL, "Error: Argument must be 1", ERR_NBARGS);
    if (!is_cub_file(argv[1]))
        clean_exit(NULL, "Error: File must be .cub", ERR_CUBEXT);
    fd = open_file(game, argv[1]);
    impor_cub_file(game, fd);   
    (void)fd;
    (void)textures;
    return (OK);
}
