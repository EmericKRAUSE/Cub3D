#include "../include/include.h"

int	ft_strlen(const char* str)
{
	int	i;
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_error(const char* message, int value)
{
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	return (value);
}

int	read_file(const char* filename)
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

void move(void *param)
{
	t_game *game = param;

	int move_x = 0;
	int move_y = 0;

	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_y -= 10; // Déplacer vers le haut
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_y += 10; // Déplacer vers le bas
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_x -= 10; // Déplacer vers la gauche
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_x += 10; // Déplacer vers la droite

	if (move_x != 0 && move_y != 0)
	{
		float factor = 0.7071;
		move_x *= factor;
		move_y *= factor;
	}

	// Appliquer les déplacements normalisés
	game->player->instances->x += move_x;
	game->player->instances->y += move_y;
}

int main(int argc, char** argv)
{
	t_game game;

	if (argc != 2)
		return (ft_error("Error: Argument must be 1", 1));
	if (read_file(argv[1]) == -1)
		return (ft_error("Error: error while reading the file", 1));
	
	// Init
	mlx_set_setting(MLX_MAXIMIZED, true);
	game.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D", true);
	game.player = mlx_new_image(game.mlx, WIN_WIDTH, WIN_HEIGHT);


	for (int y = 0; y < 50; y++)
		for (int x = 0; x < 50; x++)
			mlx_put_pixel(game.player, x, y, 0x008000FF);
	mlx_image_to_window(game.mlx, game.player, 0, 0);

	// Quit the program
	mlx_loop_hook(game.mlx, move, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);

	return (0);
}
