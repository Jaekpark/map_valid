/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 18:17:15 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/18 23:01:09 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_color_exist(t_cub *cub)
{
	if (cub->floor_color == -1 || cub->ceiling_color == -1)
		return (print_error(COLOR_ERR));
	return (1);
}

int		check_file_open(char *path)
{
	int fd;

	fd = 0;
	if ((fd = open(path, O_RDONLY)) < 0)
		return (-1);
	else if (fd >= 3)
		close(fd);
	return (1);	
}

int		check_path_exist(t_cub *cub)
{
	printf("check path %s\n", cub->path->north);
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

int		check_tex_file(t_game *game)
{
	int i;
	int fd;

	i = 0;
	fd = 0;
	while (i <= CE_TEX)
	{
		if (!(fd = open(game->tex[i].path, O_RDONLY)))
			return (print_error(NO_TEX));
		else if (fd >= 3)
			close(fd);
		i++;
	}
	return (1);
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
int 	is_tex(char *line)
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
