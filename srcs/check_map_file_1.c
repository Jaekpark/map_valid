/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_check_map_file_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 14:42:19 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/20 14:17:15 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_tex(char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		return (N_TEX);
	else if (ft_strncmp(line, "SO", 2) == 0)
		return (S_TEX);
	else if (ft_strncmp(line, "EA", 2) == 0)
		return (E_TEX);
	else if (ft_strncmp(line, "WE", 2) == 0)
		return (W_TEX);
	else if (ft_strncmp(line, "S ", 2) == 0)
		return (SP_TEX);
	else if (ft_strncmp(line, "FT", 2) == 0)
		return (FL_TEX);
	else if (ft_strncmp(line, "ST", 2) == 0)
		return (CE_TEX);
	return (-1);
}

int		check_path_exist(t_cub *cub)
{
	if (check_file_open(cub->path->north) == -1)
		return (print_error(NO_TEX));
	if (check_file_open(cub->path->south) == -1)
		return (print_error(NO_TEX));
	if (check_file_open(cub->path->east) == -1)
		return (print_error(NO_TEX));
	if (check_file_open(cub->path->west) == -1)
		return (print_error(NO_TEX));
	if (check_file_open(MID_WALL_PATH) == -1)
		return (print_error(NO_TEX));
	if (cub->sprite_cnt == 1 && check_file_open(cub->path->sprite) == -1)
		return (print_error(NO_TEX));
	if (check_file_open(cub->path->ceil) == 1)
		cub->c_tex = 1;
	if (check_file_open(cub->path->floor) == 1)
		cub->f_tex = 1;
	return (1);
}

int		check_resolution(char *line)
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

int		check_identifier(char *line)
{
	if (line[0] == 0)
		return (EMPTY_LINE);
	if (ft_strncmp(line, "R ", 2) == 0)
		return (RESOLUTION);
	else if (is_tex(line) >= 0)
		return (is_tex(line));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (FL_COL);
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (CE_COL);
	else if (ft_strchr(VALID_CHAR, line[0]) && ft_ismap(line) == 1)
		return (MAP_LINE);
	else if (ft_strchr(VALID_CHAR, line[0]) && ft_ismap(line) == -1)
		return (print_error(UNABLE_MAP_CHAR));
	else
		return (print_error(print_error(PARSING_ERR)));
}
