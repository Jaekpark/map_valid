/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_set_ray_cast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:08:37 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/15 18:52:03 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_sprite_ray(t_game *game, t_sprite *item)
{
	item->ray.x = item->sp.x - game->player.x;
	item->ray.y = item->sp.y - game->player.y;
	item->inv = 1.0 / (game->plane.x * game->dir.y - game->dir.x * game->plane.y);
	item->trans.x = item->inv * (game->dir.y * item->ray.x - game->dir.x * item->ray.y);
	item->trans.y = item->inv * (-game->plane.y * item->ray.x + game->plane.x * item->ray.y);
	item->screen_x = (int)((game->width / 2) * (1 + item->trans.x / item->trans.y));
	item->v_mv_screen = (int)(item->v_mv / item->trans.y);
	item->sp_height = (int)fabs((game->height / item->trans.y) / item->v_div);
	item->start_y = -item->sp_height / 2 + game->height / 2 + item->v_mv_screen;
	item->end_y = item->sp_height / 2 + game->height / 2 + item->v_mv_screen;
	if (item->start_y < 0)
		item->start_y = 0;
	if (item->end_y >= game->height)
		item->end_y = game->height - 1;
	item->sp_width = (int)fabs((game->height / item->trans.y) / item->u_div);
	item->start_x = -item->sp_width / 2 + item->screen_x;
	item->end_x = item->sp_width / 2 + item->screen_x;
	if (item->start_x < 0)
		item->start_x = 0;
	if (item->end_x >= game->width)
		item->end_x = game->width - 1;
}

void	set_floor_ray(t_game *game, t_floor *floor, int y)
{
	set_pos(&floor->ray_dir_l, game->dir.x - game->plane.x, game->dir.y - game->plane.y);
	set_pos(&floor->ray_dir_r, game->dir.x + game->plane.x, game->dir.y + game->plane.y);
	floor->pos_y = y - (int)game->height / 2;
	floor->half = 0.5 * game->height;
	floor->row_dist = floor->half / floor->pos_y;
	floor->step.x = floor->row_dist * (floor->ray_dir_r.x - floor->ray_dir_l.x) / game->width;
	floor->step.y = floor->row_dist * (floor->ray_dir_r.y - floor->ray_dir_l.y) / game->width; 
	floor->fl.x = game->player.x + floor->row_dist * floor->ray_dir_l.x;
	floor->fl.y = game->player.y + floor->row_dist * floor->ray_dir_l.y;
}

void	set_wall_ray(t_game *game, t_raycast *raycast, int x)
{
	raycast->camera_x = 2 * x / (double)game->width - 1;
	raycast->ray_dir.x = game->dir.x + game->plane.x * raycast->camera_x;
	raycast->ray_dir.y = game->dir.y + game->plane.y * raycast->camera_x;
	raycast->map_x = (int)game->player.x;
	raycast->map_y = (int)game->player.y;
	raycast->delta_dist.x = fabs(1 / raycast->ray_dir.x);
	raycast->delta_dist.y = fabs(1 / raycast->ray_dir.y);
	raycast->hit = 0;
}

void	set_side_dist(t_game *game, t_raycast *raycast)
{
	if (raycast->ray_dir.x < 0)
	{
		raycast->step_x = -1;
		raycast->side_dist.x = (game->player.x - raycast->map_x) * raycast->delta_dist.x;
	}
	else
	{
		raycast->step_x = 1;
		raycast->side_dist.x = (raycast->map_x + 1.0 - game->player.x) * raycast->delta_dist.x;
	}
	if (raycast->ray_dir.y < 0)
	{
		raycast->step_y = -1;
		raycast->side_dist.y = (game->player.y - raycast->map_y) * raycast->delta_dist.y;
	}
	else
	{
	raycast->step_y = 1;
	raycast->side_dist.y = (raycast->map_y + 1.0 - game->player.y) * raycast->delta_dist.y;	
	}
}

void	set_draw_wall_param(t_game *game, t_raycast *raycast)
{
	if (raycast->side == 0)
		raycast->perp_wall_dist = (raycast->map_x - game->player.x + (1 - raycast->step_x) / 2) / raycast->ray_dir.x;
	else
		raycast->perp_wall_dist = (raycast->map_y - game->player.y + (1 - raycast->step_y) / 2) / raycast->ray_dir.y;
	raycast->line_height = (int)(game->height / raycast->perp_wall_dist);
	raycast->draw_start = -raycast->line_height / 2 + game->height / 2;
	raycast->draw_end = raycast->line_height / 2 + game->height / 2;
	if (raycast->draw_start < 0)
		raycast->draw_start = 0;
	if (raycast->draw_end >= game->height)
		raycast->draw_end = game->height - 1;
	if (raycast->side == 0)
		raycast->wall_x = game->player.y + raycast->perp_wall_dist * raycast->ray_dir.y;
	else
		raycast->wall_x = game->player.x + raycast->perp_wall_dist * raycast->ray_dir.x;
	raycast->wall_x -= floor(raycast->wall_x);
	raycast->tex_idx = game->cub->map_buffer[raycast->map_x][raycast->map_y] - 52;
}
