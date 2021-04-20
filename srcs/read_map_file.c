/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:30:50 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/20 15:42:59 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			put_path(char **dest, char *src)
{
	if (!src)
		return (print_error(PARSING_ERR));
	if (*dest)
		return (print_error(DOUBLE_PATH));
	else
		*dest = ft_strdup(src);
	return (1);
}

int			parse_line(t_cub *cub, char *line, int eof)
{
	int		ret;
	int		index;

	ret = 0;
	if ((index = check_identifier(line)) < 0)
		return (-1);
	if (eof == 0 && index == EMPTY_LINE)
		return (1);
	if (cub->is_map == 1 && (index >= N_TEX && index <= EMPTY_LINE))
		return (print_error(IDEN_IN_MAP));
	else if (index >= N_TEX && index <= CE_TEX)
		ret = parsing_path(cub, line, index);
	else if (index == FL_COL || index == CE_COL)
		ret = parsing_color(cub, line, index);
	else if (index == RESOLUTION)
		ret = parsing_resolution(cub, line);
	else if (index == MAP_LINE)
		ret = parsing_map(cub, line);
	return (ret);
}

int			read_cub(t_cub *cub, int fd)
{
	int		eof;
	int		ret;
	char	*line;

	ret = 0;
	eof = 1;
	if (!cub || fd < 3)
		return (-1);
	while ((eof = get_next_line(fd, &line)) >= 0)
	{
		if (cub->is_map == 1 && line[0] == 0)
			cub->is_map = 2;
		ret = parse_line(cub, line, eof);
		free(line);
		if (ret < 0 || eof <= 0)
			break ;
	}
	close(fd);
	if (ret != -1 && eof == 0)
		ret = list_to_buffer(cub);
	return (ret);
}
