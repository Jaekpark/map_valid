/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:30:53 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/12 01:14:07 by jaekpark         ###   ########.fr       */
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

t_tex	*init_tex(t_tex *path)
{
	if (!(path = malloc(sizeof(t_tex))))
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

t_tex	*init_base_tex(t_tex *path)
{
	if (!(path = malloc(sizeof(t_tex))))
		return (NULL);
	path->north = ft_strdup("./textures/bluestone.xpm");
	path->south = ft_strdup("./textures/redbrick.xpm");
	path->east = ft_strdup("./textures/purplestone.xpm");
	path->west = ft_strdup("./textures/colorstone.xpm");
	path->sprite = ft_strdup("./textures/barrel.xpm");
	path->floor = ft_strdup("./textures/wood.xpm");
	path->ceil = ft_strdup("./textures/greystone.xpm");
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

int		**clear_texture(int **texture)
{
	int i;

	i = -1;
	while (texture[++i] != NULL)
		free(texture[i]);
	free(texture);
	texture = NULL;
	return (NULL);
}

int		**init_texture(int **texture, int width, int height, int count)
{
	int i;
	int j;

	if (!(texture = malloc(sizeof(int *) * (count))))
		return (NULL);
	i = -1;
	while (++i < count)
		if (!(texture[i] = malloc(sizeof(int) * (width * height))))
			return (clear_texture(texture));
	i = -1;
	while (++i < count)
	{
		j = 0;
		while (j < width * height)
		{
			texture[i][j] = 0;
			j++;
		}
	}
	return (texture);
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
	game->tex_height = 64;
	game->tex_width = 64;
	game->texture = init_texture(game->texture, game->tex_height, game->tex_width, 7);
	game->mv_speed = 0.05;
	game->rot_speed = 0.05;
	set_pos(&game->mv_hor, 0, 0);
	set_pos(&game->mv_ver, 0, 0);
	set_pos(&game->plane, 0, 0.66);
	set_pos(&game->player, cub->player.x, cub->player.y);
	set_pos(&game->dir, cub->dir.x, cub->dir.y);
	return (game);
}
