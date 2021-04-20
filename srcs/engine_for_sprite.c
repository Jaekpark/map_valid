/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_for_sprite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:46:45 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/20 14:38:46 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_casting(t_game *game, t_sprite *sp, int stripe)
{
	int y;
	int d;
	int tex_w;
	int tex_h;

	d = 0;
	y = sp->start_y;
	sp->color = 0;
	tex_w = game->tex[SP_TEX].width;
	tex_h = game->tex[SP_TEX].height;
	sp->tex_x = (int)((256 * (stripe - (-sp->w / 2 + sp->screen_x))
					* tex_w / sp->w) / 256);
	if (sp->trans.y > 0 && stripe > 0 && stripe < game->width
		&& sp->trans.y < game->z_buf[stripe])
	{
		while (y < sp->end_y)
		{
			d = (y - sp->mv_screen) * 256 - game->height * 128 + sp->h * 128;
			sp->tex_y = ((d * tex_h) / sp->h) / 256;
			sp->color = game->tex[SP_TEX].data[tex_w * sp->tex_y + sp->tex_x];
			if ((sp->color & 0x00FFFFFF) != 0)
				game->buf[y][stripe] = sp->color;
			y++;
		}
	}
}
