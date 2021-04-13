/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 18:17:15 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/12 16:17:05 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		fix_texture_path(t_path *path, t_path *base_path)
{
	if (path->north == NULL)
		path->north = ft_strdup(base_path->north);
	if (path->south == NULL)
		path->south = ft_strdup(base_path->south);
	if (path->east == NULL)
		path->east = ft_strdup(base_path->east);
	if (path->west == NULL)
		path->west = ft_strdup(base_path->west);
	if (path->sprite == NULL)
		path->sprite = ft_strdup(base_path->sprite);
	if (path->floor == NULL)
		path->floor = ft_strdup(base_path->floor);
	if (path->ceil == NULL)
		path->ceil = ft_strdup(base_path->ceil);
}

int		check_file_name(const char *file_name)
{
	int pos;

	pos = 0;
	if (!file_name)
		return (-1);
	if (ft_strlen((char *)file_name) < 5)
		return (-1);
	pos = ft_strlen((char *)file_name) - 4;
	while (pos--)
		file_name++;
	return (ft_strcmp((char *)file_name, MAP_EXTENSION));
}

int		check_file_extension(char *file, char *extension)
{
	int pos;

	pos = 0;
	if (!file || !extension)
		return (-1);
	if (ft_strlen(file) <= ft_strlen(extension))
		return (-1);
	pos = ft_strlen(file) - ft_strlen(extension);
	while (pos--)
		file++;
	return (ft_strcmp(file, extension));
}

int		check_option(const char *option)
{
	if (!option)
		return (-1);
	if (ft_strlen((char *)option) != ft_strlen(SAVE))
		return (-1);
	return (ft_strcmp((char *)option, SAVE));
}

int		check_identifier(char *line)
{
	if (line[0] == 0)
		return (EMPTY_LINE);
	else if (ft_strncmp(line, "R ", 2) == 0)
		return (RESOLUTION);
	else if (ft_strncmp(line, "NO", 2) == 0)
		return (NORTH_TEX);
	else if (ft_strncmp(line, "SO", 2) == 0)
		return (SOUTH_TEX);
	else if (ft_strncmp(line, "EA", 2) == 0)
		return (EAST_TEX);
	else if (ft_strncmp(line, "WE", 2) == 0)
		return (WEST_TEX);
	else if (ft_strncmp(line, "S ", 2) == 0)
		return (SPRITE_TEX);
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (FLOOR_COL);
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (CEIL_COL);
	else if (ft_strncmp(line, "FT", 2) == 0)
		return (FLOOR_TEX);
	else if (ft_strncmp(line, "ST", 2) == 0)
		return (CEIL_TEX);
	else if (ft_ismap(line) == 1)
		return (MAP_LINE);
	else
		return (-1);
}

int		check_argv(int argc, char **argv, t_cub *cub)
{
	int fd;

	fd = 0;
	if (argc < 2)
		return (print_error(NO_ARG));
	else if (argc >= 2)
	{
		if (check_file_name(argv[1]) != 0)
			return (print_error(WRONG_NAME));
		if ((fd = open(argv[1], O_RDONLY)) < 0)
			return (print_error(OPEN_ERR));
		if (argc >= 3)
		{
			if (check_option(argv[2]) != 0)
				return (print_error(WRONG_OPT));
			else if ((check_option(argv[2])) == 0)
				cub->save_opt = 1;
		}
	}
	return (fd);
}
