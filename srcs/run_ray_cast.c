/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_ray_cast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:34:59 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/20 20:27:37 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw(t_game *game)
{
	t_game	*g;
	t_win	*w;
	int		x;
	int		y;

	y = 0;
	g = game;
	w = game->window;
	while (y < (int)g->height)
	{
		x = -1;
		while (++x < (int)g->width)
			g->window->screen.data[y * (int)g->width + x] = g->buf[y][x];
		y++;
	}
	mlx_put_image_to_window(w->ptr, w->win, w->screen.img, 0, 0);
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
			floor_casting(game, &game->floor, x, y);
	}
	x = -1;
	while (++x < game->width)
		wall_casting(game, x);
	if (game->cub->sprite_cnt == 1)
	{
		set_sprite_ray(game, &game->sprite);
		stripe = game->sprite.start_x;
		while (stripe < game->sprite.end_x)
		{
			sprite_casting(game, &game->sprite, stripe);
			stripe++;
		}
	}
}

int		main_loop(t_game *game)
{
	calc(game);
	draw(game);
	key_update(game);
	return (0);
}
