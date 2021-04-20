/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_for_raycasting.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:09:43 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/20 18:45:17 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	init_sprite(t_sprite *sprite)
{
	sprite->color = 0;
	sprite->trans.x = 0;
	sprite->trans.y = 0;
	sprite->v_mv = 0;
	sprite->u_div = 1;
	sprite->v_div = 1;
	sprite->mv_screen = 0;
	sprite->w = 0;
	sprite->h = 0;
	sprite->screen_x = 0;
	sprite->start_x = 0;
	sprite->start_y = 0;
	sprite->end_x = 0;
	sprite->end_y = 0;
	sprite->tex_x = 0;
	sprite->tex_y = 0;
	sprite->inv = 0;
}

void	init_key(t_key *key)
{
	key->a = 0;
	key->w = 0;
	key->esc = 0;
	key->s = 0;
	key->d = 0;
	key->q = 0;
	key->e = 0;
}
