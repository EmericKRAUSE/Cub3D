/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/03/03 22:24:02 by nidionis         ###   ########.fr       */
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

/*
int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (ft_error("Error: Argument must be 1", 1));

	if (map_parser(&game.map, argv[1]) == -1)
		return (ft_error("Error: error while read the file", 1));

	printf ("WIDTH: %d\nHEIGHT: %d\n", WIN_WIDTH, WIN_HEIGHT);

	game.player.start_x = 5;
	game.player.start_y = 5;

	init_game(&game);
	if (DISPLAY_MODE == RENDER_3D)
		display_3d_map(&game);
	else if (DISPLAY_MODE == RENDER_2D)
		display_map(game);

	mlx_loop_hook(game.mlx, movements, &game);
	mlx_loop_hook(game.mlx, update_ray, &game);

	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free_map(&game.map);
	
	return (0);
}
*/

int	main(int argc, char **argv)
{
	t_game	*game;

    (void)game;
    (void)argc;
    game = ft_calloc(sizeof(t_game), 1);
	printf("[parse args] %i\n", parse_args(argc, argv, game));
    clean_exit(game, "Ciao", 0);
}
