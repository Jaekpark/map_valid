/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:30:53 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/06 17:36:00 by jaekpark         ###   ########.fr       */
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
	cub->player.pos_x = 0;
	cub->player.pos_y = 0;
	cub->invalid_map = 0;
	cub->map_buffer = NULL;
	cub->map = init_list(cub->map);
	cub->path = init_tex(cub->path);
	return (cub);
}
