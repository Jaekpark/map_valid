/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:35:56 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/20 15:36:31 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_tex_img(t_game *game, t_tex *t, char *path)
{
	void	*tmp;

	tmp = game->window->ptr;
	if (!game || !path)
		return ;
	t->path = ft_strdup(path);
	t->img = mlx_xpm_file_to_image(tmp, path, &t->width, &t->height);
	t->data = (int *)mlx_get_data_addr(t->img, &t->bpp, &t->size_l, &t->endian);
}

void	load_tex(t_game *game)
{
	if (!game)
		return ;
	load_tex_img(game, &game->tex[N_TEX], game->cub->path->north);
	load_tex_img(game, &game->tex[S_TEX], game->cub->path->south);
	load_tex_img(game, &game->tex[E_TEX], game->cub->path->east);
	load_tex_img(game, &game->tex[W_TEX], game->cub->path->west);
	load_tex_img(game, &game->tex[M_TEX], MID_WALL_PATH);
	if (game->cub->sprite_cnt == 1)
		load_tex_img(game, &game->tex[SP_TEX], game->cub->path->sprite);
	if (game->cub->f_tex == 1)
		load_tex_img(game, &game->tex[FL_TEX], game->cub->path->floor);
	if (game->cub->c_tex == 1)
		load_tex_img(game, &game->tex[CE_TEX], game->cub->path->ceil);
}
