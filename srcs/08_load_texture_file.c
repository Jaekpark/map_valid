/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_load_texture_file.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:35:56 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/20 02:23:10 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_tex_img(t_game *game, t_tex *tex, char *path)
{
	if (!game || !path)
		return ;
	tex->path = ft_strdup(path);
	tex->img = mlx_xpm_file_to_image(game->window->ptr, path, &tex->width, &tex->height);
	tex->data = (int *)mlx_get_data_addr(tex->img, &tex->bpp, &tex->size_l, &tex->endian);
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
	if(game->cub->sprite_cnt == 1)
		load_tex_img(game, &game->tex[SP_TEX], game->cub->path->sprite);
	if (game->cub->f_tex == 1)
		load_tex_img(game, &game->tex[FL_TEX], game->cub->path->floor);
	if (game->cub->c_tex == 1)
		load_tex_img(game, &game->tex[CE_TEX], game->cub->path->ceil);
}
