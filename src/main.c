/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/02/06 14:44:33 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

#define WALL_WIDTH 80
#define WALL_HEIGHT 80

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

void	move(void *param)
{
	t_game	*game;
	int		move_x;
	int		move_y;

	game = param;
	move_x = 0;
	move_y = 0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_y -= game->movement_distance;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_y += game->movement_distance;
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_x -= game->movement_distance;
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_x += game->movement_distance;
	if (move_x != 0 && move_y != 0)
	{
		move_x *= game->diagonal_factor;
		move_y *= game->diagonal_factor;
	}
	game->player->instances->x += move_x;
	game->player->instances->y += move_y;
}

void draw_square(mlx_t *mlx, mlx_image_t *img, uint32_t color)
{
	int	x;
	int	y;

	y = 0;
	while (y < WALL_HEIGHT)
	{
		x = 0;
		while (x < WALL_WIDTH)
		{
			mlx_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
	mlx_image_to_window(mlx, img, 0, 0);
}

// int init_map(const char *filename, char **map)
// {
// 	char buffer;
// 	int fd;
// 	ssize_t byte_read;

// 	fd = open(filename, O_RDONLY);
// 	if (fd == -1)
// 		return (-1);
// 	while ((byte_read = read(fd, &buffer, 1)) > 0)
// 		write(1, &buffer, 1);
// 	if (byte_read == -1)
// 	{
// 		close(fd);
// 		return (-1);
// 	}
// 	close(fd);
// 	return (1);
// }

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (ft_error("Error: Argument must be 1", 1));
	if (read_file(argv[1]) == -1)
		return (ft_error("Error: error while reading the file", 1));

	mlx_set_setting(MLX_MAXIMIZED, true);
	init_game(&game);
	//init_map();
	draw_square(game.mlx, game.player, 0x008000FF);
	mlx_loop_hook(game.mlx, move, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
