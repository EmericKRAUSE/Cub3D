/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 14:23:47 by ekrause           #+#    #+#             */
/*   Updated: 2025/02/12 18:00:44 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/include.h"

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
		move_y -= game->player.move_dist;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_y += game->player.move_dist;
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_x -= game->player.move_dist;
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_x += game->player.move_dist;
	if (move_x != 0 && move_y != 0)
	{
		move_x *= game->diagonal_factor;
		move_y *= game->diagonal_factor;
	}
	game->player.image->instances->x += move_x;
	game->player.image->instances->y += move_y;
}

void direction(void *param)
{
	t_game *game;
	float new_angle;
	
	game = param;
	new_angle = game->player.angle;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		new_angle -= game->player.rotation_speed;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		new_angle += game->player.rotation_speed;
		
	if (new_angle >= 2 * PI)
		new_angle -= 2 * PI;
		
	if (new_angle < 0)
		new_angle += 2 * PI;
	
	game->player.angle = new_angle;
	printf("%f\n", game->player.angle);
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
	while (game.map.map[y])
	{
		x = 0;
		while (game.map.map[y][x])
		{
			if (game.map.map[y][x] == '1')
				draw_square(game, game.wall, 0x800080FF, x * game.tile_size, y * game.tile_size);
			else
				draw_square(game, game.background, 0x000000FF, x * game.tile_size, y * game.tile_size);
			x++;
		}
		y++;
	}
	draw_square(game, game.player.image, 0xadd8e6FF, game.player.x * game.tile_size, game.player.y * game.tile_size);
}

void draw_line(t_game game, mlx_image_t *img, uint32_t color, int x_position, int y_position)
{
	int y;

	y = 0;
	while (y < game.tile_size * 2)
	{
		mlx_put_pixel(img, 1, y, color);
		y++;
	}
	mlx_image_to_window(game.mlx, img, x_position, y_position);
}

void display_ray(t_game game)
{
	draw_line(game, game.ray, 0Xffff00FF, game.player.x * game.tile_size, game.player.y * game.tile_size);
}

void update_ray(void *param)
{
	t_game *game;
	float x_final;
	float y_final;

	game = param;

	// Calcul des nouvelles coordonnées en fonction de l'angle du joueur
	x_final = game->player.x * game->tile_size + 50 * cos(game->player.angle); // Rayon partant de la position du joueur
	y_final = game->player.y * game->tile_size + 50 * sin(game->player.angle); // Rayon partant de la position du joueur

	// Mettre à jour la position du rayon
	game->ray->instances->x = x_final;
	game->ray->instances->y = y_final;

	// Redessiner le rayon
	display_ray(*game); // Redessiner le rayon à sa nouvelle position
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
	display_ray(game);

	mlx_loop_hook(game.mlx, move, &game);
	mlx_loop_hook(game.mlx, direction, &game);
	mlx_loop_hook(game.mlx, update_ray, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free_map(&game.map);
	return (0);
}
