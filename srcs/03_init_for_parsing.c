/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_init_for_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:09:38 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/19 15:10:27 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


t_list	*init_list(t_list *list)
{
	if (!(list = malloc(sizeof(t_list))))
		return (NULL);
	list->curr = NULL;
	list->head = NULL;
	list->tail = NULL;
	return (list);
}

t_path	*init_tex(t_path *path)
{
	if (!(path = malloc(sizeof(t_path))))
		return (NULL);
	path->north = NULL;
	path->south = NULL;
	path->east = NULL;
	path->west = NULL;
	path->ceil = NULL;
	path->floor = NULL;
	path->sprite = NULL;
	return (path);
}

t_cub	*init_cub(t_cub *cub)
{
	if (!(cub = malloc(sizeof(t_cub))))
		return (NULL);
	cub->f_tex = 0;
	cub->c_tex = 0;
	cub->is_map = 0;
	cub->save_opt = 0;
	cub->width = -1;
	cub->height = -1;
	cub->cols = 0;
	cub->rows = 0;
	cub->floor_color = -1;
	cub->ceiling_color = -1;
	cub->player.x = 0;
	cub->player.y = 0;
	cub->sprite.x = 0;
	cub->sprite.y = 0;
	cub->direction = 0;
	cub->invalid_map = 0;
	cub->sprite_cnt = 0;
	cub->map_buffer = NULL;
	cub->map = init_list(cub->map);
	cub->path = init_tex(cub->path);
	return (cub);
}

t_win 	*init_win(t_cub *cub, t_win *window)
{
	if (!(window = malloc(sizeof(t_win))))
		return (NULL);
	window->ptr = mlx_init();
	mlx_get_screen_size(window->ptr, &window->sys_width, &window->sys_height);
	set_screen_size(cub, window);
	window->win = mlx_new_window(window->ptr, (int)window->screen_size.x, (int)window->screen_size.y, "cub3D");
	window->screen.img = mlx_new_image(window->ptr, (int)window->screen_size.x, (int)window->screen_size.y);
	window->screen.data = (int *)mlx_get_data_addr(window->screen.img, &window->screen.bpp, &window->screen.size_l, &window->screen.endian);
	return (window);
}

t_game 	*init_game(t_cub *cub, t_game *game)
{
	if (!(game = malloc(sizeof(t_game))))
		return (NULL);
	if (!(game->window = init_win(cub, game->window)))
	{
		clear_window(game->window);
		return (NULL);
	}
	game->mv_speed = 0.1;
	game->rot_speed = 0.1;
	game->cub = cub;
	game->width = (int)game->window->screen_size.x;
	game->height = (int)game->window->screen_size.y;
	set_screen_buf(game);
	init_key(&game->key);
	set_pos(&game->sprite.sp, cub->sprite.x, cub->sprite.y);
	set_pos(&game->plane, 0, 0);
	set_pos(&game->player, cub->player.x + 0.5, cub->player.y + 0.5);
	set_pos(&game->dir, 0, 0);
	return (game);
}
