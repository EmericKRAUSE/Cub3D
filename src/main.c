/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/02/22 16:22:21 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube3d.h>

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_error(const char *message, int value)
{
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	return (value);
}

int	read_file(const char *filename)
{
	char	buffer;
	int		fd;
	ssize_t	byte_read;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	while ((byte_read = read(fd, &buffer, 1)) > 0)
		write(1, &buffer, 1);
	if (byte_read == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (ft_error("Error: Argument must be 1", 1));

	if (map_parser(&game.map, argv[1]) == -1)
		return (ft_error("Error: error while read the file", 1));

	printf ("WIDTH: %d\nHEIGHT: %d\n", WIN_WIDTH, WIN_HEIGHT);

	game.player.x = 5;
	game.player.y = 5;

	init_game(&game);
	display_map(game);

	mlx_loop_hook(game.mlx, movements, &game);
	mlx_loop_hook(game.mlx, update_ray, &game);

	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free_map(&game.map);
	
	return (0);
}
