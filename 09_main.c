#include "cub3d.h"

int main_loop(t_game *game)
{
	calc(game);
	draw(game);
	key_update(game);
	return (0);
}
