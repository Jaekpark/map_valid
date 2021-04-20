/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_for_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 12:29:20 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/20 14:52:36 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	texel_to_screen(t_game *game, t_raycast *ray, int x)
{
	int	color;
	int	y;

	color = 0;
	y = ray->draw_start;
	ray->tex_x = (int)(ray->wall_x * (double)game->tex[ray->tex_idx].width);
	if (ray->side == 0 && ray->ray_dir.x > 0)
		ray->tex_x = game->tex[ray->tex_idx].width - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir.y < 0)
		ray->tex_x = game->tex[ray->tex_idx].width - ray->tex_x - 1;
	ray->step = 1.0 * game->tex[ray->tex_idx].height / ray->line_height;
	ray->tex_pos = (ray->draw_start - game->height
					/ 2 + ray->line_height / 2) * ray->step;
	while (y < ray->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos & (game->tex[ray->tex_idx].height - 1);
		ray->tex_pos += ray->step;
		color = game->tex[ray->tex_idx].data[game->tex[ray->tex_idx].height
				* ray->tex_y + ray->tex_x];
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		game->buf[y][x] = color;
		y++;
	}
	game->z_buf[x] = ray->perp_wall_dist;
}

void	dda(t_game *game, t_raycast *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->cub->map_buffer[ray->map_x][ray->map_y] >= '4')
			ray->hit = 1;
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
