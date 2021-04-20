/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_for_cast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:08:37 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/20 16:14:12 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_sprite_ray(t_game *g, t_sprite *sp)
{
	sp->ray.x = sp->sp.x - g->player.x;
	sp->ray.y = sp->sp.y - g->player.y;
	sp->inv = 1.0 / (g->plane.x * g->dir.y - g->dir.x * g->plane.y);
	sp->trans.x = sp->inv * (g->dir.y * sp->ray.x - g->dir.x * sp->ray.y);
	sp->trans.y = sp->inv * (-g->plane.y * sp->ray.x + g->plane.x * sp->ray.y);
	sp->screen_x = (int)((g->width / 2) * (1 + sp->trans.x / sp->trans.y));
	sp->mv_screen = (int)(sp->v_mv / sp->trans.y);
	sp->h = (int)fabs((g->height / sp->trans.y) / sp->v_div);
	sp->start_y = -sp->h / 2 + g->height / 2 + sp->mv_screen;
	sp->end_y = sp->h / 2 + g->height / 2 + sp->mv_screen;
	if (sp->start_y < 0)
		sp->start_y = 0;
	if (sp->end_y >= g->height)
		sp->end_y = g->height - 1;
	sp->w = (int)fabs((g->height / sp->trans.y) / sp->u_div);
	sp->start_x = -sp->w / 2 + sp->screen_x;
	sp->end_x = sp->w / 2 + sp->screen_x;
	if (sp->start_x < 0)
		sp->start_x = 0;
	if (sp->end_x >= g->width)
		sp->end_x = g->width - 1;
}

void	set_floor_ray(t_game *g, t_floor *f, int y)
{
	set_pos(&f->ray_dir_l, g->dir.x - g->plane.x, g->dir.y - g->plane.y);
	set_pos(&f->ray_dir_r, g->dir.x + g->plane.x, g->dir.y + g->plane.y);
	f->pos_y = y - (int)g->height / 2;
	f->half = 0.5 * g->height;
	f->row_dist = f->half / f->pos_y;
	f->step.x = f->row_dist * (f->ray_dir_r.x - f->ray_dir_l.x) / g->width;
	f->step.y = f->row_dist * (f->ray_dir_r.y - f->ray_dir_l.y) / g->width;
	f->fl.x = g->player.x + f->row_dist * f->ray_dir_l.x;
	f->fl.y = g->player.y + f->row_dist * f->ray_dir_l.y;
}

void	set_wall_ray(t_game *g, t_raycast *ray, int x)
{
	ray->camera_x = 2 * x / (double)g->width - 1;
	ray->ray_dir.x = g->dir.x + g->plane.x * ray->camera_x;
	ray->ray_dir.y = g->dir.y + g->plane.y * ray->camera_x;
	ray->map_x = (int)g->player.x;
	ray->map_y = (int)g->player.y;
	ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
	ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
	ray->hit = 0;
}

void	set_side_dist(t_game *g, t_raycast *ray)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist.x = (g->player.x - ray->map_x) * ray->delta_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist.x = (ray->map_x + 1.0 - g->player.x) * ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist.y = (g->player.y - ray->map_y) * ray->delta_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist.y = (ray->map_y + 1.0 - g->player.y) * ray->delta_dist.y;
	}
}

void	set_for_draw(t_game *g, t_raycast *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - g->player.x + (1 - ray->step_x) / 2)
								/ ray->ray_dir.x;
	else
		ray->perp_wall_dist = (ray->map_y - g->player.y + (1 - ray->step_y) / 2)
								/ ray->ray_dir.y;
	ray->line_height = (int)(g->height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + g->height / 2;
	ray->draw_end = ray->line_height / 2 + g->height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= g->height)
		ray->draw_end = g->height - 1;
	if (ray->side == 0)
		ray->wall_x = g->player.y + ray->perp_wall_dist * ray->ray_dir.y;
	else
		ray->wall_x = g->player.x + ray->perp_wall_dist * ray->ray_dir.x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_idx = g->cub->map_buffer[ray->map_x][ray->map_y] - 52;
}
