#include "cub3d.h"

void	load_img(t_game *game, int *texture, char *path, t_img *img)
{
	int x;
	int y;

	y = -1;
	x = -1;
	printf("load img \n");
	img->img = mlx_xpm_file_to_image(game->window->ptr, path, &game->tex_width, &game->tex_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	while (++y < game->tex_height)
		while(++x < game->tex_width)
			texture[game->tex_width * y + x] = img->data[game->tex_width * y + x];
	mlx_destroy_image(game->window->ptr, img->img);
}

void	load_texture(t_game *game)
{
	printf("load tex \n");
	printf("%ld\n", sizeof(game->texture[8]));
	load_img(game, game->texture[NORTH_TEX], game->cub->path->north, &game->window->screen);
	load_img(game, game->texture[SOUTH_TEX], game->cub->path->south, &game->window->screen);
	load_img(game, game->texture[EAST_TEX], game->cub->path->east, &game->window->screen);
	load_img(game, game->texture[WEST_TEX], game->cub->path->west, &game->window->screen);
	load_img(game, game->texture[SPRITE_TEX], game->cub->path->sprite, &game->window->screen);
	load_img(game, game->texture[FLOOR_TEX], game->cub->path->floor, &game->window->screen);
	load_img(game, game->texture[CEIL_TEX], game->cub->path->ceil, &game->window->screen);
}
