/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_game_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:31:09 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/20 21:07:39 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_screen_buf(t_game *game)
{
	int i;
	int height;

	i = -1;
	height = game->height;
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
			break ;
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
	map = NULL;
}

void	clear_path(t_path *path)
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
	path = NULL;
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
		map_buffer[i] = NULL;
		i++;
	}
	free(map_buffer);
	map_buffer = NULL;
}

void	clear_texture(t_game *game, t_tex *tex)
{
	if (tex->path != NULL)
	{
		free(tex->path);
		tex->path = NULL;
	}
	if (tex->img != NULL)
	{
		mlx_destroy_image(game->window->ptr, tex->img);
		tex->img = NULL;
		tex->data = NULL;
	}
}
