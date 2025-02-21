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

void draw_square(t_game game, mlx_image_t *img, uint32_t color, int x_position, int y_position)
{
	int	x;
	int	y;

	y = 0;
	while (y < game.tile_size)
	{
		x = 0;
		while (x < game.tile_size)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
	mlx_image_to_window(game.mlx, img, x_position, y_position);
}

void	display_map(t_game game)
{
	int	x;
	int	y;

	y = 0;
	while (game.map.tab[y])
	{
		x = 0;
		while (game.map.tab[y][x])
		{
			if (game.map.tab[y][x] == '1')
				draw_square(game, game.wall, 0x800080FF, x * game.tile_size, y * game.tile_size);
			else
				draw_square(game, game.background, 0x000000FF, x * game.tile_size, y * game.tile_size);
			x++;
		}
		y++;
	}
	mlx_image_to_window(game.mlx, game.player.image, game.player.x * game.tile_size, game.player.y * game.tile_size);
}

int main(int argc, char **argv)
{
	t_game game;

	printf("[parse_args] %d\n", parse_args(argc, argv, &game));
}

/*
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
	ray_casting(&game);

	mlx_loop_hook(game.mlx, move, &game);
	mlx_loop_hook(game.mlx, update_ray, &game);

	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free_map(&game.map);
	
	return (0);
}
*/