/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_set_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:03:40 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/18 20:48:05 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int		set_default_config(t_game *game, t_cub *cub, int fd)
// {
// 	int ret;

// 	ret = 0;
// 	if (fd >= 3)
// 	{
// 		if ((ret = read_cub(cub, fd)) == -1)
// 			return (close_cub(cub));
// 		if ((ret = map_validation(cub)) == -1)
// 			return (close_cub(cub));
// 		if (!(game = init_game(cub, game)))
// 			return (close_cub(cub));
// 		set_player_dir(game, cub);
// 		init_raycast(&game->raycast);
// 		init_floor(&game->floor);
// 		init_sprite(&game->sprite);
// 		load_tex(game);
// 	}
// 	return (1);
// }

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

void	set_screen_size(t_cub *cub, t_win *window)
{
	if (window->sys_width <= cub->width)
	{
		window->screen_size.x = window->sys_width;
		window->screen_size.y = window->sys_width * D_RATIO;
	}
	else if (cub->width < 640)
	{
		window->screen_size.x = 640;
		window->screen_size.y = 640 * D_RATIO;
	}
	else
	{
		window->screen_size.x = cub->width;
		window->screen_size.y = cub->width * D_RATIO;
	}
}
