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
    {
        clean_exit(game, "Error: File not found", ERR_OPENFILE);
    }
    return (fd);
}

t_textures *get_textures(char *filename)
{
    (void)filename;
    return (NULL);
}

int parse_args(int argc, char **argv, t_game *game)
{
    int fd;
    t_textures *textures;

    if (argc != 2)
        return (ft_error("Error: Argument must be 1", 1));
    fd = open_file(game, argv[1]);
    textures = get_textures(argv[1]);   
    (void)fd;
    (void)textures;
    return (0);
}