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

int is_blank_line(char *line)
{
    if (!line)
        return (FALSE);
    else
        while (*line)
            if (!ft_strchr(BLANK_CHAR, *line++))
                return (FALSE);
    return (TRUE);
}

int is_map(char *line)
{
    if (!line || is_blank_line(line))
        return (FALSE);
    else
        while (!is_blank_line(line))
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
    if (!texture_balise)
        clean_exit(game, "Error: malloc failed", ERR_MALLOC);
    i = 0;
    found = FALSE;
    if (!line)
        return (FALSE);
    else
        while (texture_balise[i] && !found)
            if (ft_strncmp(line, texture_balise[i++], 3) == CMP_FOUND)
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
    //print_tab(map);
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

int get_texture_ind_from_balise(char *balise)
{
    if (ft_strncmp(balise, "NO ", 3) == CMP_FOUND)
        return (NORTH);
    else if (ft_strncmp(balise, "SO ", 3) == CMP_FOUND)
        return (SOUTH);
    else if (ft_strncmp(balise, "WE ", 3) == CMP_FOUND)
        return (WEST);
    else if (ft_strncmp(balise, "EA ", 3) == CMP_FOUND)
        return (EAST);
    return (BALISE_ERROR);
}

int get_texture(t_game *game, char *line)
{
    int ind;

    ind = get_texture_ind_from_balise(line);
    if (ind == BALISE_ERROR)
        clean_exit(game, "Error: Invalid texture balise", ERR_LOADING_TEXTURE);
    return (load_texture(game, ind, line));
}

int impor_cub_file(t_game *game)
{
    char *line;

    line = get_next_line(game->fd);
    game->map.tab = NULL;
    while (line)
    {
        if (is_blank(line))
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
        //if (is_color(game, line))
        //    if (get_color(game, line) == ERR_LOADING_TEXTURE)
        //        clean_exit(game, "[get_color] something went wrong", ERR_COLOR);
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

void print_game(t_game *game)
{
    //printf("fd: %d\n", game->fd);
    printf("map:\n");
    print_tab(game->map.tab);
    printf("\n");
    printf("north: %s\n", game->textures.f_names[NORTH]);
    printf("south: %s\n", game->textures.f_names[SOUTH]);
    printf("west: %s\n", game->textures.f_names[WEST]);
    printf("east: %s\n", game->textures.f_names[EAST]);
}

int parse_args(int argc, char **argv, t_game *game)
{
    t_textures *textures;

    if (argc != 2)
        clean_exit(NULL, "Error: Argument must be 1", ERR_NBARGS);
    if (!is_cub_file(argv[1]))
        clean_exit(NULL, "Error: File must be .cub", ERR_CUBEXT);
    game->fd = open_file(game, argv[1]);
    impor_cub_file(game);
    print_game(game);
    (void)textures;
    return (OK);
}
