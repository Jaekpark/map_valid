/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 19:40:53 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/20 19:41:10 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mv_forward_back(t_game *game, char **map_buffer)
{
	if (game->key.w)
	{
		if (map_buffer[(int)(game->player.x + game->dir.x
			* game->mv_speed)][(int)(game->player.y)] == '0')
			game->player.x += game->dir.x * game->mv_speed;
		if (map_buffer[(int)(game->player.x)][(int)(game->player.y
			+ game->dir.y * game->mv_speed)] == '0')
			game->player.y += game->dir.y * game->mv_speed;
	}
	else if (game->key.s)
	{
		if (map_buffer[(int)(game->player.x - game->dir.x
			* game->mv_speed)][(int)(game->player.y)] == '0')
			game->player.x -= game->dir.x * game->mv_speed;
		if (map_buffer[(int)(game->player.x)][(int)(game->player.y
			- game->dir.y * game->mv_speed)] == '0')
			game->player.y -= game->dir.y * game->mv_speed;
	}
	else if (game->key.esc)
		exit_game(game);
}

void	rot_right_left(t_game *game)
{
	double old_dir_x;
	double old_plane_x;
	double rot;

	old_dir_x = game->dir.x;
	old_plane_x = game->plane.x;
	rot = game->rot_speed;
	if (game->key.e)
	{
		game->dir.x = game->dir.x * cos(-rot) - game->dir.y * sin(-rot);
		game->dir.y = old_dir_x * sin(-rot) + game->dir.y * cos(-rot);
		game->plane.x = game->plane.x * cos(-rot) - game->plane.y * sin(-rot);
		game->plane.y = old_plane_x * sin(-rot) + game->plane.y * cos(-rot);
	}
	else if (game->key.q)
	{
		game->dir.x = game->dir.x * cos(rot) - game->dir.y * sin(rot);
		game->dir.y = old_dir_x * sin(rot) + game->dir.y * cos(rot);
		game->plane.x = game->plane.x * cos(rot) - game->plane.y * sin(rot);
		game->plane.y = old_plane_x * sin(rot) + game->plane.y * cos(rot);
	}
	if (game->key.esc)
		exit_game(game);
}

void	mv_right_left(t_game *game, char **map_buffer)
{
	if (game->key.d)
	{
		if (map_buffer[(int)(game->player.x + game->plane.x
			* game->mv_speed)][(int)(game->player.y)] == '0')
			game->player.x += (game->plane.x * game->mv_speed);
		if (map_buffer[(int)(game->player.x)][(int)(game->player.y
			+ game->plane.y * game->mv_speed)] == '0')
			game->player.y += (game->plane.y * game->mv_speed);
	}
	else if (game->key.a)
	{
		if (map_buffer[(int)(game->player.x - game->plane.x
			* game->mv_speed)][(int)(game->player.y)] == '0')
			game->player.x -= (game->plane.x * game->mv_speed);
		if (map_buffer[(int)(game->player.x)][(int)(game->player.y
			- game->plane.y * game->mv_speed)] == '0')
			game->player.y -= (game->plane.y * game->mv_speed);
	}
}
