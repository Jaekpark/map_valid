/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_game_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:20:42 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/20 21:05:24 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		clear_cub(t_cub *cub)
{
	if (!cub)
		return (-1);
	if (cub->path != NULL)
		clear_path(cub->path);
	cub->path = NULL;
	if (cub->map != NULL)
		clear_map(cub->map);
	clear_map_buffer(cub->map_buffer);
	cub->map = NULL;
	free(cub);
	cub = NULL;
	return (-1);
}

void	clear_buf(t_game *game)
{
	int i;
	int height;

	i = -1;
	height = game->height;
	if (game->z_buf != NULL)
	{
		free(game->z_buf);
		game->z_buf = NULL;
	}
	if (game->buf != NULL)
	{
		while (++i < height)
			free(game->buf[i]);
		free(game->buf);
		game->buf = NULL;
	}
}

void	clear_tex(t_game *game)
{
	int i;

	i = -1;
	while (++i <= M_TEX)
	{
		if (game->tex[i].img != NULL && game->tex[i].data != NULL)
		{
			if (game->tex[i].path != NULL)
			{
				free(game->tex[i].path);
				game->tex[i].path = NULL;
			}
			mlx_destroy_image(game->window->ptr, game->tex[i].img);
			game->tex[i].img = NULL;
			game->tex[i].data = NULL;
		}
	}
	if (game->cub->sprite_cnt == 1)
		clear_texture(game, &game->tex[SP_TEX]);
	if (game->cub->f_tex == 1)
		clear_texture(game, &game->tex[FL_TEX]);
	if (game->cub->c_tex == 1)
		clear_texture(game, &game->tex[CE_TEX]);
}

void	clear_window(t_win *window)
{
	if (window->screen.img)
		mlx_destroy_image(window->ptr, window->screen.img);
	if (window->ptr && window->win)
		mlx_destroy_window(window->ptr, window->win);
	free(window);
	window = NULL;
}

void	clear_game(t_game *game)
{
	if (!game)
		return ;
	clear_tex(game);
	if (game->cub != NULL)
		clear_cub(game->cub);
	if (game->window != NULL)
		clear_window(game->window);
	if (game->buf != NULL || game->z_buf != NULL)
		clear_buf(game);
	free(game);
	game = NULL;
}
