/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_for_floor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:45:12 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/20 14:50:59 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	floor_tex_casting(t_game *game, t_floor *floor, int x, int y)
{
	int color;

	color = 0;
	floor->tex_x = (int)(game->tex[FL_TEX].width * (floor->fl.x - floor->ce_x))
					& (game->tex[FL_TEX].width - 1);
	floor->tex_y = (int)(game->tex[FL_TEX].height * (floor->fl.y - floor->ce_y))
					& (game->tex[FL_TEX].height - 1);
	color = game->tex[FL_TEX].data[game->tex[FL_TEX].width
			* floor->tex_y + floor->tex_x];
	color = (color >> 1) & 8355711;
	game->buf[y][x] = color;
}

void	ceil_tex_casting(t_game *game, t_floor *floor, int x, int y)
{
	int color;

	color = 0;
	floor->tex_x = (int)(game->tex[CE_TEX].width * (floor->fl.x - floor->ce_x))
					& (game->tex[CE_TEX].width - 1);
	floor->tex_y = (int)(game->tex[CE_TEX].height * (floor->fl.y - floor->ce_y))
					& (game->tex[CE_TEX].height - 1);
	color = game->tex[CE_TEX].data[game->tex[CE_TEX].width
					* floor->tex_y + floor->tex_x];
	color = (color >> 1) & 8355711;
	game->buf[game->height - y - 1][x] = color;
}

void	floor_casting(t_game *game, t_floor *floor, int x, int y)
{
	floor->ce_x = (int)(floor->fl.x);
	floor->ce_y = (int)(floor->fl.y);
	floor->fl.x += floor->step.x;
	floor->fl.y += floor->step.y;
	if (game->cub->f_tex == 1)
		floor_tex_casting(game, floor, x, y);
	else if (game->cub->f_tex == 0)
		game->buf[y][x] = game->cub->floor_color;
	if (game->cub->c_tex == 1)
		ceil_tex_casting(game, floor, x, y);
	else if (game->cub->c_tex == 0)
		game->buf[game->height - y - 1][x] = game->cub->ceiling_color;
}
