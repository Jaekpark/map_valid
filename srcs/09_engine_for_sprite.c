/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_engine_for_sprite.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:46:45 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/20 02:37:32 by jaekpark         ###   ########.fr       */
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
