/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:30:50 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/18 14:21:06 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void print_game(t_game *game)
{
	printf("========== t_game ===========\n");
	printf("|player x, y = %f, %f|\n", game->player.x, game->player.y);
	printf("|plane  x, y = %f, %f|\n", game->plane.x, game->plane.y);
	printf("|game dir x, y = %f, %f|\n", game->dir.x, game->dir.y);
	printf("|mv_speed, rot_speed = %f, %f|\n", game->mv_speed, game->rot_speed);
	printf("|sprite x,y = %f, %f\n", game->sprite.sp.x, game->sprite.sp.y);
	printf("|screen size = %f, %f|\n", game->window->screen_size.x, game->window->screen_size.y);
	printf("|texture[0] height, width bpp = %d, %d, %d|\n", game->tex[1].height, game->tex[1].width, game->tex[1].bpp);
	printf("---------t_game end----------\n");
}

void print_path(t_path *path)
{
	printf("north = %s\n", path->north);
	printf("soutn = %s\n", path->south);
	printf("east = %s\n", path->east);
	printf("east = %s\n", path->west);
	printf("sprite = %s\n", path->sprite);
	printf("floor = %s\n", path->floor);
	printf("ceil = %s\n", path->ceil);
}

void print_cub(t_cub *cub)
{
	printf("=================t_cub===============\n");
	printf("direction = %c\n", cub->direction);
	printf("width, height = %d, %d\n", cub->width, cub->height);
	printf("cols rows = %d, %d\n", cub->cols, cub->rows);
	printf("save opt = %d\n", cub->save_opt);
	printf("sprtie x,y = %f, %f\n", cub->sprite.x, cub->sprite.y);
	printf("floor color = %d, ceil color = %d\n", cub->floor_color, cub->ceiling_color);
	printf("invalid map = %d\n", cub->invalid_map);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	printf("map buffer\n");
	print_double_ptr(cub->map_buffer);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	printf("map _list\n");
	print_node(cub->map);
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	printf("player pos x, y = %f, %f\n", cub->player.x, cub->player.y);
	printf("+++++  path  +++++++\n");
	print_path(cub->path);
	printf("---------------- t_cub end -------------\n");
}

void print_node(t_list *list)
{
	t_node *temp;

	temp = list->head;
	if (temp == NULL)
		printf("NULL\n");
	while (temp != NULL)
	{
		printf("%s\n", temp->line);
		temp = temp->next;
	}
}

void	print_double_ptr(char **s)
{
	int i;

	i = -1;
	while (s[++i] != NULL)
		printf("str[%2d] = |%s|\n", i, s[i]);
}

int		parse_line(t_cub *cub, char *line, int eof)
{
	int ret;
	int index;

	ret = 0;
	if ((index = check_identifier(line)) < 0)
		return (-1);
	if (eof == 0 && index == EMPTY_LINE)
		return (1);
	if (cub->is_map == 1 && (index >= N_TEX && index <= EMPTY_LINE))
		return (-1);
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

int		read_cub(t_cub *cub, int fd)
{
	int 	eof;
	int 	ret;
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
			break;
	}
	close(fd);
	if (ret != -1 && eof == 0)
		ret = list_to_buffer(cub);
	return (ret);
}
