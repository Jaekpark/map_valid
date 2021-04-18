/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 18:03:47 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/18 22:50:48 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int put_path(char **dest, char *src)
{
	printf("put _path %s\n", *dest);
	if (!src)
		return (print_error(PARSING_ERR));
	if (*dest)
		return (print_error(DOUBLE_PATH));
	else
		*dest = ft_strdup(src);
	return (1);
}

int parsing_path(t_cub *cub, char *line, int index)
{
	char **path;
	int ret;

	ret = 0;
	if ((check_file_extension(line, TEX_EXTENSION)) != 0)
		return (print_error(TEX_EXT));
	path = ft_split(line, ' ');
	if (index == N_TEX)
		ret = put_path(&cub->path->north, path[1]);
	else if (index == S_TEX)
		ret = put_path(&cub->path->south, path[1]);
	else if (index == E_TEX)
		ret = put_path(&cub->path->east, path[1]);
	else if (index == W_TEX)
		ret =put_path(&cub->path->west, path[1]);
	else if (index == SP_TEX)
		ret = put_path(&cub->path->sprite, path[1]);
	else if (index == FL_TEX)
		ret = put_path(&cub->path->floor, path[1]);
	else if (index == CE_TEX)
		ret = put_path(&cub->path->ceil, path[1]);
	double_ptr_mem_free(path);
	return (ret);
}

int	check_resolution(char *line)
{
	int i;

	i = -1;
	while (line[++i] != '\0')
	{
		if (line[i] != ' ' && (ft_isnum(line[i]) != 1))
			return (-1);
	}
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

int	check_color_overlap(t_cub *cub, int index)
{
	if (index == FL_COL && cub->floor_color != -1)
		return (-1);
	else if (index == CE_COL && cub->ceiling_color != -1)
		return (-1);
	return (1);
}

int parsing_color(t_cub *cub, char *line, int index)
{
	int rgb;
	char **color;

	rgb = -1;
	if (check_color_overlap(cub, index) == -1)
		return (print_error(COLOR_ERR));
	if ((check_color_char(line + 1) < 0) || (check_color_space(line + 1) < 0))
		return (print_error(COLOR_ERR));
	if (!(color = ft_split(line + 1, ',')))
		return (print_error(COLOR_ERR));
	if ((rgb = make_color(color)) < 0)
	{
		double_ptr_mem_free(color);	
		return (print_error(COLOR_ERR));
	}
	if (index == CE_COL)
		cub->ceiling_color = rgb;
	else if (index == FL_COL)
		cub->floor_color = rgb;
	double_ptr_mem_free(color);
	return (1);
}

int parsing_resolution(t_cub *cub, char *line)
{
	int i;
	int ret;
	char **display_size;

	i = 0;
	ret = 0;
	if (cub->width != 0 || cub->height != 0)
		ret = -1;
	if (((check_resolution(line + 1)) == -1) || ret == -1)
		return (print_error(WRONG_RES));
	display_size = ft_split(line, ' ');
	while (display_size[i])
		i++;
	if (i != 3)
		return (print_error(WRONG_RES));
	cub->width = ft_atoi(display_size[1]);
	cub->height = ft_atoi(display_size[2]);
	double_ptr_mem_free(display_size);
	return (1);	
}

int 	parsing_map(t_cub *cub, char *line)
{
	t_list	*tmp;
	t_node	*node;

	if (cub->is_map == 2)
		return (print_error(AFTER_EMPTY));
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
