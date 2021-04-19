/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_utils_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 14:59:54 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/19 18:33:13 by jaekpark         ###   ########.fr       */
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
	printf("|window size_l = %d wid bpp = %d|\n", game->window->screen.size_l, game->window->screen.bpp);
	printf("|data size = %d|\n", game->window->screen.data[2]);
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
