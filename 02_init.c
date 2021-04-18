/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:30:53 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/18 14:19:15 by jaekpark         ###   ########.fr       */
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
	sprite->trans.x = 0;
	sprite->trans.y = 0;
	sprite->v_mv = 0;
	sprite->u_div = 1;
	sprite->v_div = 1;
	sprite->v_mv_screen = 0;
	sprite->sp_width = 0;
	sprite->sp_height = 0;
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
}

void	clear_buf(t_game *game)
{
	int i;
	int height;

	i = -1;
	height = (int)game->window->screen_size.y;
	if (game->z_buf != NULL)
	{
		free(game->z_buf);
		game->z_buf = NULL;
	}
	if (game->buf != NULL)
	{
		while (++i < height)
			free(game->buf[i]);
		free(game->buf);
		game->buf = NULL;
	}
}

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
	cub->is_map = 0;
	cub->save_opt = 0;
	cub->width = 0;
	cub->height = 0;
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
