#ifndef CUBE3D_H
# define CUBE3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>

// ####################
// Macros

// General
# define WIN_WIDTH 2560
# define WIN_HEIGHT (WIN_WIDTH * 9 / 16)
# define FOV 60
# define FOV_RAD (FOV * (M_PI / 180))

// Display mode
# define RENDER_3D 1
# define RENDER_2D 0
# define DISPLAY_MODE RENDER_2D

// Color management
# define HEX_BLACK 0x000000FF
# define HEX_WHITE 0xFFFFFFFF
# define HEX_YELLOW 0xFFFF00FF
# define HEX_BLUE 0x77B5FEFF
# define HEX_BROWN 0x5C4033DF

# define COLOR_PLAYER HEX_WHITE
# define COLOR_RAY HEX_YELLOW
# define COLOR_WALL HEX_WHITE
# define COLOR_BACKGROUND HEX_BLACK
# define COLOR_CEILING HEX_BLUE
# define COLOR_FLOOR HEX_BROWN

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

# define ERR_OPENFILE -1

	// ####################
	// Structures
	typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_player
{
	mlx_image_t	*image;
	int			start_x;
	int			start_y;
	int			move_dist;
	float		angle;
	float		rotation_speed;
}	t_player;

typedef struct s_map
{
	char	**tab;
	int		width;
	int		height;
}	t_map;

typedef struct s_textures
{
	char	*f_names[4];
} 	t_textures;

typedef struct s_game
{
	mlx_t		*mlx;
	int			tile_size;
	mlx_image_t	*ray;
	float		ray_distances[WIN_WIDTH];
	t_map		map;
	t_player	player;
	mlx_image_t *wall;
	mlx_image_t	*background;
	mlx_image_t *world;
	t_textures	textures;
}	t_game;

// ####################
// Prototypes
void	display_map(t_game game);
void	display_3d_map(t_game *game);
void	display_world(void *param);
void	init_game(t_game* game);
void	movements(void *param);
int		map_parser(t_map *map, char *filename);
void	ray_casting(t_game *game);
void	update_ray(void *param);
void	free_map(t_map *map);

// ####################
// utils
void clean_exit(t_game *game, char *msg, int exit_code);

int	ft_error(const char *message, int value);

#endif