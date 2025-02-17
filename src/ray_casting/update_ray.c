#include "../../include/include.h"

void update_ray(void *param)
{
	t_game *game;

	game = param;
	cast_ray(game);
}
