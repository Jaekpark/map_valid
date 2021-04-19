/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_engine_for_wall.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 12:29:20 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/19 15:53:36 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	texel_to_screen(t_game *game, t_raycast *raycast, int x)
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

void	wall_casting(t_game *game, int x)
{
	set_wall_ray(game, &game->raycast, x);
	set_side_dist(game, &game->raycast);
	dda(game, &game->raycast);
	set_for_draw(game, &game->raycast);
	texel_to_screen(game, &game->raycast, x);
}
