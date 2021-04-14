/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_ray_cast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 12:29:20 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/14 17:52:20 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_sprite(t_game *game, t_sprite *item)
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
	tex_width = game->texture[SPRITE_TEX].width;
	tex_height = game->texture[SPRITE_TEX].height;
	item->tex_x = (int)((256 * (stripe - (-item->sp_width / 2 + item->screen_x)) * tex_width / item->sp_width) / 256);
	if (item->trans.y > 0 && stripe > 0 && stripe < game->width && item->trans.y < game->z_buf[stripe])
	{
		while (y < item->end_y)
		{
			d = (y - item->v_mv_screen) * 256 - game->height * 128 + item->sp_height * 128;
			item->tex_y = ((d * tex_height) / item->sp_height) / 256;
			color = game->texture[SPRITE_TEX].data[tex_width * item->tex_y + item->tex_x];
			if ((color & 0x00FFFFFF) != 0)
				game->buf[y][stripe] = color;
			y++;
		}
	}

}
void	init_floor(t_floor *floor)
{
	floor->half = 0;
	floor->row_dist = 0;
	floor->pos_y = 0;
	floor->tex_x = 0;
	floor->tex_y = 0;
	floor->ce_x = 0;
	floor->ce_y = 0;
	set_pos(&floor->fl, 0, 0);
	set_pos(&floor->step, 0, 0);
	set_pos(&floor->ray_dir_l, 0, 0);
	set_pos(&floor->ray_dir_r, 0, 0);
}

void	init_raycast(t_raycast *raycast)
{
	raycast->camera_x = 0;
	raycast->draw_end = 0;
	raycast->draw_start = 0;
	raycast->hit = 0;
	raycast->line_height = 0;
	raycast->perp_wall_dist = 0;
	raycast->side = 0;
	raycast->map_x = 0;
	raycast->map_y = 0;
	raycast->step_x = 0;
	raycast->step_y = 0;
	raycast->wall_x = 0;
	raycast->tex_idx = 0;
	raycast->tex_pos = 0;
	raycast->tex_x = 0;
	raycast->tex_y = 0;
	raycast->step = 0;
	set_pos(&raycast->delta_dist, 0, 0);
	set_pos(&raycast->ray_dir, 0, 0);
	set_pos(&raycast->side_dist, 0, 0);
}

void	draw(t_game *game)
{
	int x;
	int y;

	y = 0;
	while (y < (int)game->height)
	{
		x = -1;
		while (++x < (int)game->width)
			game->window->screen.data[y * (int)game->width + x] = game->buf[y][x];
		y++;
	}
	mlx_put_image_to_window(game->window->ptr, game->window->win, game->window->screen.img, 0, 0);
}

void	coord_tex(t_game *game, t_raycast *raycast, int x)
{
	int color;
	int y;

	color = 0;
	y = raycast->draw_start;
	raycast->tex_x = (int)(raycast->wall_x * (double)game->texture[raycast->tex_idx].width);
	if (raycast->side == 0 && raycast->ray_dir.x > 0)
		raycast->tex_x = game->texture[raycast->tex_idx].width - raycast->tex_x - 1;
	if (raycast->side == 1 && raycast->ray_dir.y < 0)
		raycast->tex_x = game->texture[raycast->tex_idx].width - raycast->tex_x - 1;
	raycast->step = 1.0 * game->texture[raycast->tex_idx].height / raycast->line_height;
	raycast->tex_pos = (raycast->draw_start - game->height / 2 + raycast->line_height / 2) * raycast->step;
	while (y < raycast->draw_end)
	{
		raycast->tex_y = (int)raycast->tex_pos & (game->texture[raycast->tex_idx].height - 1);
		raycast->tex_pos += raycast->step;
		color = game->texture[raycast->tex_idx].data[game->texture[raycast->tex_idx].height * raycast->tex_y + raycast->tex_x];
		if (raycast->side == 1)
			color = (color >> 1) & 8355711;
		game->buf[y][x] = color;
		y++;
	}
	game->z_buf[x] = raycast->perp_wall_dist;
}

void	set_draw_param(t_game *game, t_raycast *raycast)
	{
// 	printf("*********** enter set draw param ***********\n");
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
	raycast->tex_idx = game->cub->map_buffer[raycast->map_x][raycast->map_y] - 49;
	// printf("1. perp wall dist = %f\n2. line_height = %d\n3. draw start, end = %d, %d\n4. wall_x = %f\n5. tex_idx = %d\n", raycast->perp_wall_dist, raycast->line_height, raycast->draw_start, raycast->draw_end, raycast->wall_x,raycast->tex_idx);
	// printf("^^^^^^^^^^^^^^^^^^^end set drawparam^^^^^^^^^^^^^\n");

}

void	dda(t_game *game, t_raycast *raycast)
{
	// printf("&&&&&&&&&&& enter dda $$$$$$$$$$$$\n");
	// printf("before dda hit = %d\n", raycast->hit);
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
		if (game->cub->map_buffer[raycast->map_x][raycast->map_y] == '1')
			raycast->hit = 1;
	}
	// printf("-----------@@ dda @@------------\n");
	// printf("1. side_dist = %f, %f\n2. map x, y = %d, %d\n3. side = %d\n4. hit = %d\n", raycast->side_dist.x, raycast->side_dist.y, raycast->map_x, raycast->map_y, raycast->side, raycast->hit);
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
	// printf("--------------@@  set side dist @@ ---------------\n");
	// printf("1. step_x, y = %d, %d\n2. side_dist x,y = %f, %f\n", raycast->step_x, raycast->step_y, raycast->side_dist.x, raycast->side_dist.y);

}

void	set_ray(t_game *game, t_raycast *raycast, int x)
{
	raycast->camera_x = 2 * x / (double)game->width - 1;
	raycast->ray_dir.x = game->dir.x + game->plane.x * raycast->camera_x;
	raycast->ray_dir.y = game->dir.y + game->plane.y * raycast->camera_x;
	raycast->map_x = (int)game->player.x;
	raycast->map_y = (int)game->player.y;
	raycast->delta_dist.x = fabs(1 / raycast->ray_dir.x);
	raycast->delta_dist.y = fabs(1 / raycast->ray_dir.y);
	raycast->hit = 0;
	// printf("------------@@@ set ray @@@----------------------\n");
	// printf("1. camera_x = %f\n2. raydir x,y = %f, %f\n3. map x,y = %d, %d\n4. delta_dist x,y = %f, %f\n", raycast->camera_x, raycast->ray_dir.x, raycast->ray_dir.y, raycast->map_x, raycast->map_y, raycast->delta_dist.x, raycast->delta_dist.y);
	
}	


void	floor_cast(t_game *game, t_floor *floor, int x, int y)
{
	int color;

	color = 0;
	floor->ce_x = (int)(floor->fl.x);
	floor->ce_y = (int)(floor->fl.y);
	floor->tex_x = (int)(game->texture[FLOOR_TEX].width * (floor->fl.x - floor->ce_x)) & (game->texture[FLOOR_TEX].width - 1);
	floor->tex_y = (int)(game->texture[FLOOR_TEX].height * (floor->fl.y - floor->ce_y)) & (game->texture[FLOOR_TEX].height - 1);
	floor->fl.x += floor->step.x;
	floor->fl.y += floor->step.y;
	color = game->texture[5].data[game->texture[5].width * floor->tex_y + floor->tex_x];
	color = (color >> 1) & 8355711;
	game->buf[y][x] = color;
	color = game->texture[CEIL_TEX].data[game->texture[CEIL_TEX].width * floor->tex_y + floor->tex_x];
	color = (color >> 1) & 8355711;
	game->buf[(int)game->height - y - 1][x] = color;
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
void	wall_casting(t_game *game, int x)
{
	set_ray(game, &game->raycast, x);
	set_side_dist(game, &game->raycast);
	dda(game, &game->raycast);
	set_draw_param(game, &game->raycast);
	coord_tex(game, &game->raycast, x);
}

void	calc(t_game *game)
{
	int x;
	int y;
	int stripe;

	y = -1;
	while (++y < game->height)
	{
		set_floor_ray(game, &game->floor, y);
		x = -1;
		while (++x < game->width)
			floor_cast(game, &game->floor, x, y);
	}
	x = -1;
	while (++x < game->width)
		wall_casting(game, x);
		// set_ray(game, &game->raycast, x);
		// set_side_dist(game, &game->raycast);
		// dda(game, &game->raycast);
		// set_draw_param(game, &game->raycast);
		// coord_tex(game, &game->raycast, x);
	set_sprite(game, &game->sprite);
	stripe = game->sprite.start_x;
	//printf("stripe =  %d, %d\n", stripe, game->sprite.end_x);
	while (stripe < game->sprite.end_x)
	{
		sprite_casting(game, &game->sprite, stripe);
		stripe++;
	}
}


int main_loop(t_game *game)
{
	calc(game);
	draw(game);
	key_update(game);
	return (0);
}
