/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:30:53 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/11 16:16:04 by jaekpark         ###   ########.fr       */
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
	path->sprite = NULL;
	path->floor = NULL;
	path->ceil = NULL;
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
	cub->path = init_tex(cub->path);
	return (cub);
}

t_game 	*init_game(t_cub *cub, t_game *game)
{
	if (!(game = malloc(sizeof(t_game))))
		return (NULL);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, cub->width, cub->height, "cub3D");
	game->img.img = mlx_new_image(game->mlx, cub->width, cub->height);
	game->img.data = (int *)mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.size_l, &game->img.endian);
	game->mv_speed = 0.05;
	game->rot_speed = 0.05;
	game->mv_hor.x = 0;
	game->mv_hor.y = 0;
	game->mv_ver.x = 0;
	game->mv_ver.y = 0;
	game->plane.x = 0;
	game->plane.y = 0.66;
	game->player.x = cub->player.x;
	game->player.y = cub->player.y;
	game->dir.x = cub->dir.x;
	game->dir.y = cub->dir.y;
	return (game);
}