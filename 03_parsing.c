/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 18:03:47 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/05 12:46:25 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parsing_path(t_cub *cub, char *line, int index)
{
	char **path;

	path = ft_split(line, ' ');
	if (!path)
		return (-1);
	else if (index == NORTH_TEX)
		cub->path->north = ft_strdup(path[1]);
	else if (index == SOUTH_TEX)
		cub->path->south = ft_strdup(path[1]);
	else if (index == EAST_TEX)
		cub->path->east = ft_strdup(path[1]);
	else if (index == WEST_TEX)
		cub->path->west = ft_strdup(path[1]);
	else if (index == SPRITE_TEX)
		cub->path->sprite = ft_strdup(path[1]);
	else if (index == FLOOR_TEX)
		cub->path->floor = ft_strdup(path[1]);
	else if (index == CEIL_TEX)
		cub->path->ceil = ft_strdup(path[1]);
	split_mem_free(path);
	return (1);
}

int	check_color_space(char *line)
{
	int i;
	int num;
	int space;

	i = -1;
	num = 0;
	space = 0;
	while (line[++i] != '\0')
	{
		if (num == 0 && (ft_isnum(line[i]) == 1))
			num = 1;
		else if (num == 1 && line[i] == ' ')
			space = 1;
		else if (num == 1 && space == 1 && (ft_isnum(line[i]) == 1))
			return (-1);
		else if (line[i] == ',')
		{
			num = 0;
			space = 0;
		}
	}
	return (1);
}

int	check_color_char(char *line)
{
	int i;
	int comma;
	
	i = -1;
	comma = 0;
	if (!line)
		return (-1);
	if (line[0] != ' ')
		return (-1);
	while (line[++i] != '\0')
	{
		if (line[i] == ',')
			comma++;
		if (comma > 2)
			return (-1);
		else if (line[i] != ' ' && line[i] != ',' && (ft_isnum(line[i]) != 1))
			return (-1);
	}
	return (1);
}

int make_color(char **color)
{
	int r;
	int g;
	int b;
	int rgb;

	if (!color)
		return (-1);
	if (color[3] != NULL)
		return (-1);
	r = ft_atoi(color[0]);
	g = ft_atoi(color[1]);
	b = ft_atoi(color[2]);
	rgb = (r << 16) | (g << 8) | b;
	return (rgb);
}

int parsing_color(t_cub *cub, char *line, int index)
{
	int rgb;
	char **color;

	rgb = -1;
	if ((check_color_char(line + 1) < 0))
		return (-1);
	if ((check_color_space(line + 1) < 0))
		return (-1);
	if (!(color = ft_split(line + 1, ',')))
		return (-1);
	if (!(rgb = make_color(color)))
	{
		split_mem_free(color);	
		return (-1);
	}
	if (index == CEIL_COL)
		cub->ceiling_color = rgb;
	else if (index == FLOOR_COL)
		cub->floor_color = rgb;
	split_mem_free(color);
	return (1);
}

int parsing_resolution(t_cub *cub, char *line)
{
	int i;
	char **display_size;

	i = 0;
	display_size = ft_split(line, ' ');
	while (display_size[i])
		i++;
	if (i != 3)
		return (-1);
	cub->width = ft_atoi(display_size[1]);
	cub->height = ft_atoi(display_size[2]);
	split_mem_free(display_size);
	return (1);	
}

int 	parsing_map(t_cub *cub, char *line)
{
	t_list	*tmp;
	t_node	*node;

	if (cub->is_map == 2)
		return (-1);
	tmp = cub->map;
	cub->is_map = 1;
	if (!(node = malloc(sizeof(t_node))))
		return (-1);
	node->line = ft_strdup(line);
	node->next = NULL;
	tmp->curr = node;
	if (tmp->curr != NULL && (tmp->head == NULL && tmp->tail == NULL))
	{
		tmp->head = tmp->curr;
		tmp->tail = tmp->curr;
	}
	else
	{
		tmp->tail->next = tmp->curr;
		tmp->tail = tmp->curr;
	}
	return (1);
}
