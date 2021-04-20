/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_run_ray_cast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:34:59 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/20 02:28:44 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int main_loop(t_game *game)
{
	calc(game);
	draw(game);
	key_update(game);
	if (game->cub->save_opt == 1)
	{
		save_bmp(game);
		exit_game(game);
	}
	return (0);
}
