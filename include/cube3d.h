#ifndef CUBE3D_H
# define CUBE3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <get_next_line.h>
# include "../lib/libft/include/libft.h"
# define WIN_WIDTH 2560
# define WIN_HEIGHT (WIN_WIDTH * 9 / 16)
# define FOV 90
# define FOV_RAD (FOV * (M_PI / 180))

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

# define CMP_FOUND 0

# define ERR_OPENFILE -1
# define ERR_MULTIPLE_MAPS -2
# define ERR_LOADING_TEXTURE -3
# define ERR_MALLOC -4
# define ERR_COLOR -5
# define ERR_TEXTURE -6
# define ERR_NBARGS -7
# define ERR_CUBEXT -8


# define MAP_CHARS "01 \n"
# define TEXTURES_BALISE "NO /SO /EA /WE "

// ####################
// Structures
typedef struct s_player
{
	mlx_image_t	*image;
	int			x;
	int			y;
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
} t_textures;

typedef struct s_game
{
	mlx_t		*mlx;
	int			tile_size;
	mlx_image_t	*ray;
	t_map		map;
	t_player	player;
	mlx_image_t *wall;
	mlx_image_t	*background;
	t_textures	textures;
}	t_game;

// ####################
// Prototypes
void	init_game(t_game* game);
void	move(void *param);
int		map_parser(t_map *map, char *filename);
void	ray_casting(t_game *game);
void	update_ray(void *param);
void	free_tab(char **tab);
void	free_map(t_map *map);

// ####################
// utils
void clean_exit(t_game *game, char *msg, int exit_code);
//char	*get_next_line(int fd);
int	ft_error(const char *message, int value);

// ####################
// parsing
int parse_args(int argc, char **argv, t_game *game);

#endif