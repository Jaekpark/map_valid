/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 16:18:59 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/13 19:10:31 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mv_forward_back(t_game *game, char **map_buffer)
{
	if (game->key.w)
	{
		if (map_buffer[(int)(game->player.x + game->dir.x * game->mv_speed)][(int)(game->player.y)] != '1')
			game->player.x += game->dir.x * game->mv_speed;
		if (map_buffer[(int)(game->player.x)][(int)(game->player.y + game->dir.y * game->mv_speed)] != '1')
			game->player.y += game->dir.y * game->mv_speed;
	}
	if (game->key.s)
	{
		if (map_buffer[(int)(game->player.x - game->dir.x * game->mv_speed)][(int)(game->player.y)] != '1')
			game->player.x -= game->dir.x * game->mv_speed;
		if (map_buffer[(int)(game->player.x)][(int)(game->player.y - game->dir.y * game->mv_speed)] != '1')
			game->player.y -= game->dir.y * game->mv_speed;
	}
	if (game->key.esc)
		exit(0);
}

void	rot_right_left(t_game *game)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = game->dir.x;
	old_plane_x = game->plane.x;
	if (game->key.d)
	{
		game->dir.x = game->dir.x * cos(-game->rot_speed) - game->dir.y * sin(-game->rot_speed);
		game->dir.y = old_dir_x * sin(-game->rot_speed) + game->dir.y * cos(-game->rot_speed);
		game->plane.x = game->plane.x * cos(-game->rot_speed) - game->plane.y * sin(-game->rot_speed);
		game->plane.y = old_plane_x * sin(-game->rot_speed) + game->plane.y * cos(-game->rot_speed);
	}
	if (game->key.a)
	{
		game->dir.x = game->dir.x * cos(game->rot_speed) - game->dir.y * sin(game->rot_speed);
		game->dir.y = old_dir_x * sin(game->rot_speed) + game->dir.y * cos(game->rot_speed);
		game->plane.x = game->plane.x * cos(game->rot_speed) - game->plane.y * sin(game->rot_speed);
		game->plane.y = old_plane_x * sin(game->rot_speed) + game->plane.y * cos(game->rot_speed);
	}
	if (game->key.esc)
		exit(0);
}

void	key_update(t_game *game)
{
	if (game->key.w || game->key.s)
		mv_forward_back(game, game->cub->map_buffer);
	if (game->key.a || game->key.d)
		rot_right_left(game);
}

int		key_press(int key, t_game *game)
{
	if (key == KEY_ESC)
		exit(0);
	else if (key == KEY_W || key == KEY_UP)
		game->key.w = 1;
	else if (key == KEY_S || key == KEY_DOWN)
		game->key.s = 1;
	else if (key == KEY_A || key == KEY_LEFT)
		game->key.a = 1;
	else if (key == KEY_D || key == KEY_RIGHT)
		game->key.d = 1;
	return (0);
}

int		key_release(int key, t_game *game)
{
	if (key == KEY_ESC)
		exit(0);
	else if (key == KEY_W || key == KEY_UP)
		game->key.w = 0;
	else if (key == KEY_S || key == KEY_DOWN)
		game->key.s = 0;
	else if (key == KEY_A || key == KEY_LEFT)
		game->key.a = 0;
	else if (key == KEY_D || key == KEY_RIGHT)
		game->key.d = 0;
	return (0);
}