NAME    =   Cub3D

# Définition des bibliothèques à utiliser : libft et minilibx
LIBRARIES = ft
LIB_NAMES = $(addprefix lib, $(LIBRARIES))

LIB_DIR = ./lib
INCLUDE_DIRS = ./include
INCLUDE_DIRS += $(addsuffix /include,$(addprefix $(LIB_DIR)/,$(LIB_NAMES)))

# Répertoires spécifiques à minilibx
LIBMLX  = ./MLX42
LIBMLX_BUILD = $(LIBMLX)/build
LIBMLX_FLAGS = -L$(LIBMLX_BUILD) -lmlx42 -ldl -lglfw -pthread -lm

# Compilateur et options
CC      	=   gcc
CFLAGS  	=   -Wall -Wextra -Werror -I include -O3 -Ofast
DEBUG_FLAGS	= -g3
LFLAGS  	=   $(LIBMLX_FLAGS)
LDFLAGS 	= $(addprefix -L$(LIB_DIR)/lib,$(LIBRARIES))
LDLIBS  	= $(addprefix -l,$(LIBRARIES))



SRC = src/get_next_line.c src/get_next_line_utils.c src/debug/print_tab.c src/main.c \
	src/display_map/display_3d_map.c src/display_map/display_minimap.c src/display_map/draw_assets.c src/display_map/rgb_to_uint32.c \
	src/door/on_space_press.c src/door/ray_casting_doors.c src/exit/clean_exit.c src/init/init_game.c \
	src/map_utils/map_utils.c src/move/move.c src/move/move_utils.c src/move/on_cursor_move.c \
	src/parsing/get_textures_and_colors.c src/parsing/import_cub.c src/parsing/line_types.c src/parsing/load_ft.c \
	src/parsing/missing_params.c src/parsing/parse_args.c src/parsing/set_player.c src/parsing/map/check.c \
	src/parsing/map/floodfill.c src/parsing/map/format_map.c src/parsing/map/get_map_brut.c src/parsing/map/surround_map.c \
	src/parsing/map/trim.c src/ray_casting/draw_slice.c src/ray_casting/find_inter.c src/ray_casting/ray_casting.c \
	src/ray_casting/ray_casting_utils.c src/ray_casting/update_ray.c

#SRC = $(shell find src -type f -name "*.c")

OBJ     =   $(SRC:.c=.o)

DEBUG_OBJ = $(SRC:.c=.debug.o)

all: libmlx make_libs $(NAME)

%.debug.o: %.c
	$(CC) $(DEBUG_FLAGS) -I include -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) $(OBJ) -o $(NAME) $(LDLIBS) $(LFLAGS)

debug: libmlx make_libs $(DEBUG_OBJ)
	$(CC) $(DEBUG_FLAGS) $(INCLUDES) $(LDFLAGS) $(DEBUG_OBJ) -o $(NAME) $(LDLIBS) $(LFLAGS)
	lldb $(NAME)
	rm $(DEBUG_OBJ)
	rm $(NAME)

libmlx: check_mlx
	@cmake $(LIBMLX) -B $(LIBMLX_BUILD) && make -C $(LIBMLX_BUILD)

	@cmake $(LIBMLX) -B $(LIBMLX_BUILD) && make -C $(LIBMLX_BUILD)

make_libs:
	for lib in $(LIB_NAMES); do \
		$(MAKE) -C $(LIB_DIR)/$$lib; \
	done

check_mlx:
	if [ ! -d "$(LIBMLX)" ]; then \
		echo "MLX42 not found, cloning..."; \
		git clone https://github.com/codam-coding-college/MLX42.git ; \
	fi

clean:
	for lib in $(LIB_NAMES); do \
		$(MAKE) -C $(LIB_DIR)/$$lib clean; \
	done
	rm -rf $(OBJ)

fclean: clean
	for lib in $(LIB_NAMES); do \
		$(MAKE) -C $(LIB_DIR)/$$lib fclean; \
	done
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re make_libs libmlx

