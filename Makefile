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
CC      =   gcc
CFLAGS  =   -Wall -Wextra -Werror -I include -g3 # -O3 -Ofast# -fsanitize=address# -fstack-protector-all
LFLAGS  =   $(LIBMLX_FLAGS)
LDFLAGS = $(addprefix -L$(LIB_DIR)/lib,$(LIBRARIES))
LDLIBS  = $(addprefix -l,$(LIBRARIES))

SRC = $(shell find src -type f -name "*.c")
## Définition des fichiers sources
#SRC     =   src/main.c\
#            src/init/init_game.c\
#            src/move/move.c\
#            src/parsing/map_parser.c\
#            src/ray_casting/cast_ray.c\
#            src/ray_casting/update_ray.c

# Fichiers objets
OBJ     =   $(SRC:.c=.o)

# Cible par défaut
all: libmlx make_libs $(NAME)

# Règle pour créer l'exécutable
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) $(OBJ) -o $(NAME) $(LDLIBS) $(LFLAGS)

# Règle pour construire la minilibx séparément
libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX_BUILD) && make -C $(LIBMLX_BUILD)

# Règle pour construire les bibliothèques (libft uniquement)
make_libs:
	for lib in $(LIB_NAMES); do \
		$(MAKE) -C $(LIB_DIR)/$$lib; \
	done

# Nettoyage des fichiers objets
clean:
	for lib in $(LIB_NAMES); do \
		$(MAKE) -C $(LIB_DIR)/$$lib clean; \
	done
	rm -rf $(OBJ)

# Nettoyage complet, y compris l'exécutable
fclean: clean
	for lib in $(LIB_NAMES); do \
		$(MAKE) -C $(LIB_DIR)/$$lib fclean; \
	done
	rm -f $(NAME)

# Recompiler tout
re: fclean all

.PHONY: all clean fclean re make_libs libmlx

