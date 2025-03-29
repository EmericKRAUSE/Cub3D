/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrause <emeric.yukii@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:13:14 by nidionis          #+#    #+#             */
/*   Updated: 2025/03/29 16:25:14 by ekrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/include/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// ####################
// Macros

// General
# define WIN_WIDTH	2560
# define WIN_HEIGHT 1440
# define FOV 60
# define SENSIVITY 2.00

// Crosshair
# define CROSSHAIR_SIZE 31
# define CROSSHAIR_THICKNESS 3

// Display mode
# define RENDER_3D 1
# define RENDER_2D 0
# define DISPLAY_MODE RENDER_3D

// Color management
# define HEX_BLACK 0x000000FF
# define HEX_WHITE 0xFFFFFFFF
# define HEX_YELLOW 0xFFFF00FF
# define HEX_BLUE 0x77B5FEFF
# define HEX_BROWN 0x5C4033DF
# define HEX_GREEN 0x008000FF
# define HEX_DARK_GREEN 0x0A5C0AFF

# define COLOR_PLAYER HEX_WHITE
# define COLOR_CROSSHAIR HEX_YELLOW
# define COLOR_RAY HEX_YELLOW
# define COLOR_WALL HEX_GREEN
# define COLOR_DOOR	HEX_WHITE
# define COLOR_WALL_NORTH HEX_GREEN
# define COLOR_WALL_SOUTH HEX_GREEN
# define COLOR_WALL_EAST HEX_DARK_GREEN
# define COLOR_WALL_WEST HEX_DARK_GREEN
# define COLOR_BACKGROUND HEX_BLACK
# define COLOR_CEILING HEX_BLUE
# define COLOR_FLOOR HEX_BROWN
# define UNSET_COLOR -1

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3
# define BALISE_ERROR -1

# define CMP_FOUND 0
# define OK 1

# define ERR_OPENFILE -1
# define ERR_MULTIPLE_MAPS -2
# define ERR_LOADING_TEXTURE -3
# define ERR_MALLOC -4
# define ERR_COLOR -5
# define ERR_TEXTURE -6
# define ERR_NBARGS -7
# define ERR_CUBEXT -8
# define ERR_INVALID_MAP -9
# define ERR_INVALID_LINE -10
# define ERR_MAP -11

# define HABIBI 000707
# define BLANK_CHAR "\t\n "
# define CHAR_BLANK_MAP '0'

# define MAP_CHARS "01DdNSEW \n"
# define TEXTURES_BALISE "NO /SO /EA /WE "
# define PLAYER_CHARS "NSEW"
# define FLOODFILL_CHARS "NSEW0"
# define FLOODFILL_VISITED 'V'

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

// ####################
// Structures
typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct s_fpoint
{
	float			x;
	float			y;
}					t_fpoint;

typedef struct s_rgb
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef struct s_player
{
	mlx_image_t		*image;
	int				start_x;
	int				start_y;
	int				move_dist;
	float			angle;
	float			rotation_speed;
}					t_player;

typedef struct s_map
{
	char			**tab;
	int				width;
	int				height;
}					t_map;

typedef struct s_textures
{
	char			*f_names[4];
	mlx_texture_t	*orientation[4];
	mlx_texture_t	*door;
	t_rgb			floor;
	t_rgb			ceiling;
} 					t_textures;

typedef struct s_images
{
	mlx_image_t		*floor;
	mlx_image_t		*ceiling;
}					t_images;

typedef struct s_slice
{
	mlx_texture_t	*texture;
	float			hit_ratio;
	float			distance;
}					t_slice;

typedef struct s_game
{
	mlx_t		*mlx;
	t_map		map;
	t_images	images;
	t_player	player;
	int			time;
	int			launcher_frame;
	int			is_shooting;
	mlx_image_t	*wall;
	mlx_image_t *door;
	mlx_image_t	*background;
	mlx_image_t	*world;
	mlx_image_t	*crosshair;
	mlx_image_t *rocket_launcher[7];
	t_textures	textures;
	int			tile_size;
	int			fd;
}	t_game;

// ####################
// Prototypes
void	display_map(t_game *game);
void	display_3d_map(t_game *game);
void	display_world(void *param);
void	init_game(t_game *game);
void	movements(void *param);
int		map_parser(t_map *map, char *filename);
void	ray_casting(t_game *game);
void	update_ray(void *param);
void	free_tab(char **tab);
void	free_map(t_map *map);
void	on_cursor_move(double xpos, double ypos, void *param);
float	find_horizontal_inter(t_game *game, float angle);
float	find_vertical_inter(t_game *game, float angle);
mlx_texture_t	texture_line(mlx_texture_t *texture, float hit_ratio);
void	draw_slice(t_game *game, int i, float ray_angle, t_slice slice);
void	on_space_press(mlx_key_data_t keydata, void *param);

// ####################
// draw_assets
void draw_gun(t_game *game);
void draw_launcher(t_game *game);

// ####################
// ray_casting_utils
int prepare_world_image(t_game *game);
void normalize_angle(float *angle);

// ####################
// utils
void				clean_exit(t_game *game, char *msg, int exit_code);
int					ft_error(const char *message, int value);

// ####################
// map_utils
char				**dup_tab(char **tab);

// ####################
// parsing
int					parse_args(int argc, char **argv, t_game *game);
char				*get_next_line(int fd);
int					import_cub_file(t_game *game);
int					is_cub_file(char *filename);

int					is_rgb(char *str);
int					is_texture(t_game *game, char *line);
int					is_map(char *line);
int					is_blank_line(char *line);
int					is_color(char *line);

int					load_texture(t_game *game, int ind, char *line);
int					get_texture(t_game *game, char *line);
int					get_color(t_game *game, char *line);
int					get_texture_ind_from_balise(char *balise);
int					get_texture(t_game *game, char *line);
t_rgb				*get_rgb(t_game *game, char *line, t_rgb *rgb);
int					get_color(t_game *game, char *line);
char				**get_map(t_game *game, int fd, char **line_addr);

char				*load_map(t_game *game, char *line);
void				invalid_line(t_game *game, char *line);
int					load_texture(t_game *game, int ind, char *line);
void				set_map_point(char **map, t_point pt, char c);
t_point				get_player_position(char **map);
int					param_missing_but_map(t_game *game);
int					param_missing(t_game *game);
int					is_map_available(t_game *game);
void				trim_map(char ***map_addr);
void				set_width_and_lenght(t_game *game);
void				set_width_and_lenght(t_game *game);
void				ft_square_map(t_game *game, char c);
int					one_player_only(char **map);
int					is_map_closed(char **map);
void				delete_blank_lines(char ***map_addr);

// ####################
// debug
void				print_tab(char **tab);
void				print_game(t_game *game);

#endif
