#include "cub3d.h"

void	load_img(t_game *game, t_tex *texture, char *path)
{
	if (!game || !path)
		return ;
	texture->img = mlx_xpm_file_to_image(game->window->ptr, path, &texture->width, &texture->height);
	texture->data = (int *)mlx_get_data_addr(texture->img, &texture->bpp, &texture->size_l, &texture->endian);
}

void	load_texture(t_game *game)
{
	if (!game)
		return ;
	load_img(game, &game->texture[NORTH_TEX], "./textures/north.xpm");
	load_img(game, &game->texture[SOUTH_TEX], "./textures/south.xpm");
	load_img(game, &game->texture[EAST_TEX], "./textures/east.xpm");
	load_img(game, &game->texture[WEST_TEX], "./textures/west.xpm");
	load_img(game, &game->texture[SPRITE_TEX], "./textures/sprite.xpm");
	load_img(game, &game->texture[FLOOR_TEX], "./textures/floor.xpm");
	load_img(game, &game->texture[CEIL_TEX], "./textures/ceil.xpm");
}
