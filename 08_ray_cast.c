/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_ray_cast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 12:29:20 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/18 17:34:20 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_casting(t_game *game, t_sprite *item, int stripe)
{
	int y;
	int d;
	int color;
	int tex_width;
	int tex_height;

	d = 0;
	color = 0;
	y = item->start_y;
	tex_width = game->tex[SP_TEX].width;
	tex_height = game->tex[SP_TEX].height;
	item->tex_x = (int)((256 * (stripe - (-item->sp_width / 2 + item->screen_x)) * tex_width / item->sp_width) / 256);
	if (item->trans.y > 0 && stripe > 0 && stripe < game->width && item->trans.y < game->z_buf[stripe])
	{
		while (y < item->end_y)
		{
			d = (y - item->v_mv_screen) * 256 - game->height * 128 + item->sp_height * 128;
			item->tex_y = ((d * tex_height) / item->sp_height) / 256;
			color = game->tex[SP_TEX].data[tex_width * item->tex_y + item->tex_x];
			if ((color & 0x00FFFFFF) != 0)
				game->buf[y][stripe] = color;
			y++;
		}
	}

}

void	coord_tex(t_game *game, t_raycast *raycast, int x)
{
	int color;
	int y;

	color = 0;
	y = raycast->draw_start;
	raycast->tex_x = (int)(raycast->wall_x * (double)game->tex[raycast->tex_idx].width);
	if (raycast->side == 0 && raycast->ray_dir.x > 0)
		raycast->tex_x = game->tex[raycast->tex_idx].width - raycast->tex_x - 1;
	if (raycast->side == 1 && raycast->ray_dir.y < 0)
		raycast->tex_x = game->tex[raycast->tex_idx].width - raycast->tex_x - 1;
	raycast->step = 1.0 * game->tex[raycast->tex_idx].height / raycast->line_height;
	raycast->tex_pos = (raycast->draw_start - game->height / 2 + raycast->line_height / 2) * raycast->step;
	while (y < raycast->draw_end)
	{
		raycast->tex_y = (int)raycast->tex_pos & (game->tex[raycast->tex_idx].height - 1);
		raycast->tex_pos += raycast->step;
		color = game->tex[raycast->tex_idx].data[game->tex[raycast->tex_idx].height * raycast->tex_y + raycast->tex_x];
		if (raycast->side == 1)
			color = (color >> 1) & 8355711;
		game->buf[y][x] = color;
		y++;
	}
	game->z_buf[x] = raycast->perp_wall_dist;
}


void	dda(t_game *game, t_raycast *raycast)
{
	while (raycast->hit == 0)
	{
		if (raycast->side_dist.x < raycast->side_dist.y)
		{
			raycast->side_dist.x += game->raycast.delta_dist.x;
			raycast->map_x += raycast->step_x;
			raycast->side = 0;
		}
		else
		{
			raycast->side_dist.y += raycast->delta_dist.y;
			raycast->map_y += raycast->step_y;
			raycast->side = 1;
		}
		if (game->cub->map_buffer[raycast->map_x][raycast->map_y] >= '4')
			raycast->hit = 1;
	}
}

void	floor_tex_casting(t_game *game, t_floor *floor, int x, int y)
{
	int color;
	
	color = 0;
	floor->tex_x = (int)(game->tex[FL_TEX].width * (floor->fl.x - floor->ce_x)) & (game->tex[FL_TEX].width - 1);
	floor->tex_y = (int)(game->tex[FL_TEX].height * (floor->fl.y - floor->ce_y)) & (game->tex[FL_TEX].height - 1);
	color = game->tex[FL_TEX].data[game->tex[FL_TEX].width * floor->tex_y + floor->tex_x];
	color = (color >> 1) & 8355711;
	game->buf[y][x] = color;
}

void	ceil_tex_casting(t_game *game, t_floor *floor, int x, int y)
{
	int color;

	color = 0;
	floor->tex_x = (int)(game->tex[CE_TEX].width * (floor->fl.x - floor->ce_x)) & (game->tex[CE_TEX].width - 1);
	floor->tex_y = (int)(game->tex[CE_TEX].height * (floor->fl.y - floor->ce_y)) & (game->tex[CE_TEX].height - 1);
	color = game->tex[CE_TEX].data[game->tex[CE_TEX].width * floor->tex_y + floor->tex_x];
	color = (color >> 1) & 8355711;
	game->buf[game->height - y - 1][x] = color;
}

void		floor_casting(t_game *game, t_floor *floor, int x, int y)
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

void	wall_casting(t_game *game, int x)
{
	set_wall_ray(game, &game->raycast, x);
	set_side_dist(game, &game->raycast);
	dda(game, &game->raycast);
	set_draw_wall_param(game, &game->raycast);
	coord_tex(game, &game->raycast, x);
}
