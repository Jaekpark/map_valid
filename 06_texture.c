#include "cub3d.h"

void	load_tex_img(t_game *game, t_tex *tex, char *path)
{
	if (!game || !path)
		return ;
	tex->img = mlx_xpm_file_to_image(game->window->ptr, path, &tex->width, &tex->height);
	tex->data = (int *)mlx_get_data_addr(tex->img, &tex->bpp, &tex->size_l, &tex->endian);
}

void	load_tex(t_game *game)
{
	if (!game)
		return ;
	load_tex_img(game, &game->tex[N_TEX], "./textures/north.xpm");
	load_tex_img(game, &game->tex[S_TEX], "./textures/south.xpm");
	load_tex_img(game, &game->tex[E_TEX], "./textures/east.xpm");
	load_tex_img(game, &game->tex[W_TEX], "./textures/west.xpm");
	load_tex_img(game, &game->tex[SP_TEX], "./textures/sprite.xpm");
	load_tex_img(game, &game->tex[FL_TEX], "./textures/floor.xpm");
	load_tex_img(game, &game->tex[CE_TEX], "./textures/ceil.xpm");
}
