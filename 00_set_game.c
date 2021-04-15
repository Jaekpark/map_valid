/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_set_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:03:40 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/15 20:29:01 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		set_default_config(t_game *game, t_cub *cub, int fd)
{
	int ret;

	ret = 0;
	if (fd >= 3)
	{
		if ((ret = read_cub(cub, fd)) == -1)
			return (close_cub(cub));
		if ((ret = map_validation(cub)) == -1)
			return (close_cub(cub));
		if (!(game = init_game(cub, game)))
			return (close_cub(cub));
		set_player_dir(game, cub);
		init_raycast(&game->raycast);
		init_floor(&game->floor);
		init_sprite(&game->sprite);
		load_tex(game);
	}
	return (1);
}

void	set_pos(t_pos *pos, double x, double y)
{
	if (!pos)
		return ;
	pos->x = x;
	pos->y = y;
}

void	set_player_dir(t_game *game, t_cub *cub)
{
	if (cub->direction == 'N')
	{
		set_pos(&game->dir, -1, 0);
		set_pos(&game->plane, 0, 0.66);
	}
	else if (cub->direction == 'S')
	{
		set_pos(&game->dir, 1, 0);
		set_pos(&game->plane, 0, -0.66);
	}	
	else if (cub->direction == 'E')
	{
		set_pos(&game->dir, 0, 1);
		set_pos(&game->plane, 0.66, 0);
	}
	else if (cub->direction == 'W')
	{
		set_pos(&game->dir, 0, -1);
		set_pos(&game->plane, -0.66, 0);
	}
	printf("$$$$$$$$$$$$$game detail = %f, %f\n", game->plane.x, game->plane.y);
}

void	set_screen_buf(t_game *game)
{
	int i;
	int width;
	int height;

	i = -1;
	width = (int)game->window->screen_size.x;
	height = (int)game->window->screen_size.y;
	if (!(game->z_buf = malloc(sizeof(double) * width)))
		return ;
	if (!(game->buf = malloc(sizeof(int *) * height)))
		return ;
	while (++i < height)
		game->buf[i] = malloc(sizeof(int) * width);
}

int		set_screen_size(t_cub *cub, t_pos *screen_size)
{
	if (!cub || !screen_size)
		return (-1);
	if (cub->width <= 640)
	{
		screen_size->x = 640;
		screen_size->y = 360;
	}
	else if (cub->width <= 1280)
	{
		screen_size->x = 1280;
		screen_size->y = 720;
	}
	else if (cub->width <= 1600)
	{
		screen_size->x = 1600;
		screen_size->y = 900;
	}
	else
	{
		screen_size->x = 1920;
		screen_size->y = 1080;
	}
	return (1);
}
