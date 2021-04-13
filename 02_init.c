/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:30:53 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/13 19:31:25 by jaekpark         ###   ########.fr       */
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
	cub->dir.x = 0;
	cub->dir.y = 0;
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
	init_key(&game->key);
	set_pos(&game->plane, 0, 0);
	set_pos(&game->player, cub->player.x, cub->player.y);
	set_pos(&game->dir, cub->dir.x, cub->dir.y);
	return (game);
}
