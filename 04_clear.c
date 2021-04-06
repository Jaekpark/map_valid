/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:31:09 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/05 12:51:30 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_map(t_list *map)
{
	t_node	*temp;

	temp = NULL;
	while (map->head != NULL)
	{
		if (map->head->next == NULL)
		{
			free(map->head->line);
			free(map->head);
			break;
		}
		temp = map->head;
		while (temp->next->next != NULL)
			temp = temp->next;
		free(temp->next->line);
		free(temp->next);
		temp->next = NULL;
		if (temp != NULL)
			map->tail = temp;
	}
	free(map);
}

void	clear_path(t_tex *path)
{
	if (!path)
		return ;
	if (path->north != NULL)
		free(path->north);
	if (path->south != NULL)
		free(path->south);
	if (path->east != NULL)
		free(path->east);
	if (path->west != NULL)
		free(path->west);
	if (path->sprite != NULL)
		free(path->sprite);
	if (path->floor != NULL)
		free(path->floor);
	if (path->ceil != NULL)
		free(path->ceil);
	free(path);
}

void	clear_map_buffer(char **map_buffer)
{
	int i;

	i = 0;
	if (!map_buffer)
		return ;
	while (map_buffer[i] != NULL)
	{
		free(map_buffer[i]);
		i++;
	}
	free(map_buffer);
}

void	clear_cub(t_cub *cub)
{
	if (!cub)
		return ;
	if (cub->path != NULL)
		clear_path(cub->path);
	cub->path = NULL;
	if (cub->map != NULL)
		clear_map(cub->map);
	clear_map_buffer(cub->map_buffer);
	cub->map = NULL;
	free(cub);
}
