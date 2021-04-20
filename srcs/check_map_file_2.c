/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_check_map_file_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 14:45:22 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/20 14:18:05 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_color_exist(t_cub *cub)
{
	if (cub->floor_color == -1 || cub->ceiling_color == -1)
		return (print_error(COLOR_ERR));
	if (cub->width == -1 || cub->height == -1)
		return (print_error(WRONG_RES));
	return (1);
}

int		check_color_overlap(t_cub *cub, int index)
{
	if (index == FL_COL && cub->floor_color != -1)
		return (-1);
	else if (index == CE_COL && cub->ceiling_color != -1)
		return (-1);
	return (1);
}

int		check_color_space(char *line)
{
	int	i;
	int	num;
	int	space;

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

int		check_color_char(char *line)
{
	int	i;
	int	comma;

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
