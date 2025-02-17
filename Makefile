NAME    =   Cub3D
CC      =   gcc
CFLAGS  =   -Wall -Wextra -Werror
LIBMLX  =   ./MLX42
LIBS    =   $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRC     =   src/main.c\
			src/init/init_game.c\
			src/move/move.c\
			src/parsing/map_parser.c\
			src/ray_casting/cast_ray.c\
			src/ray_casting/update_ray.c

OBJ     =   $(SRC:.c=.o)

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build


$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LIBS) -o $(NAME)

clean:
	rm -f $(OBJ)
	rm -rf $(LIBMLX)/build

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libmlx
