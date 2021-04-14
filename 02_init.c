/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:30:53 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/14 17:25:29 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	set_buf(t_game *game)
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

t_path	*init_base_tex(t_path *path)
{
	if (!(path = malloc(sizeof(t_path))))
		return (NULL);
	path->north = ft_strdup("./textures/north.xpm");
	path->south = ft_strdup("./textures/south.xpm");
	path->east = ft_strdup("./textures/east.xpm");
	path->west = ft_strdup("./textures/west.xpm");
	path->sprite = ft_strdup("./textures/sprite.xpm");
	path->floor = ft_strdup("./textures/floor.xpm");
	path->ceil = ft_strdup("./textures/ceil.xpm");
	return (path);
}

void	set_pos(t_pos *pos, double x, double y)
{
	if (!pos)
		return ;
	pos->x = x;
	pos->y = y;
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
	cub->floor_color = 0;
	cub->ceiling_color = 0;
	cub->player.x = 0;
	cub->player.y = 0;
	cub->sprite.x = 0;
	cub->sprite.y = 0;
	cub->direction = 0;
	cub->invalid_map = 0;
	cub->map_buffer = NULL;
	cub->map = init_list(cub->map);
	cub->base_path = init_base_tex(cub->base_path);
	cub->path = init_tex(cub->path);
	return (cub);
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

t_win 	*init_win(t_cub *cub, t_win *window)
{
	if (!(window = malloc(sizeof(t_win))))
		return (NULL);
	if (!(set_screen_size(cub, &window->screen_size)))
		return (NULL);
	window->ptr = mlx_init();
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
	set_buf(game);
	init_key(&game->key);
	set_pos(&game->sprite.sp, cub->sprite.x, cub->sprite.y);
	set_pos(&game->plane, 0, 0);
	set_pos(&game->player, cub->player.x + 0.5, cub->player.y + 0.5);
	set_pos(&game->dir, 0, 0);
	return (game);
}
