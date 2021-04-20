/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_valid_map_buffer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 11:35:54 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/19 15:33:31 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		map_dfs(t_cub *cub, char **visited, int x, int y)
{
	if (x == 0 || y == cub->cols - 1 || x == cub->rows - 1 || y == 0)
	{
		cub->invalid_map += 1;
		return ;
	}
	if (visited[x][y] == '0' || ft_isplayer(visited[x][y]) || visited[x][y] == ' ')
		visited[x][y] = 'V';
	if (x < cub->rows - 1 && (visited[x + 1][y] == '0' || visited[x + 1][y] == ' '))
		map_dfs(cub, visited, x + 1, y);
	if (x != 0 && (visited[x - 1][y] == '0' || visited[x - 1][y] == ' '))
		map_dfs(cub, visited, x - 1, y);
	if (y < cub->cols - 1 && (visited[x][y + 1] == '0' || visited[x][y + 1] == ' '))
		map_dfs(cub, visited, x, y + 1);
	if (y != 0 && (visited[x][y - 1] == '0' || visited[x][y - 1] == ' '))
		map_dfs(cub, visited, x, y - 1);
}

void		parse_wall_direction(t_cub *cub, char **visited, int x, int y)
{
	int		q_x;
	int		q_y;
	int		after_sp;
	int		before_sp;
	int		last_y;

	q_x = cub->rows / 4;
	q_y = cub->cols / 4;
	after_sp = after_space(visited);
	before_sp = before_space(visited);
	last_y = cub->cols - 1 - after_sp;
	if (x == 0 && visited[x][y] == '1')
		cub->map_buffer[x][y] = '4';
	else if (x == cub->rows - 1 && visited[x][y] == '1')
		cub->map_buffer[x][y] = '5';
	else if (((y == 0) || (y < last_y && y <= before_sp)) && visited[x][y] == '1')
		cub->map_buffer[x][y] = '6';
	else if ((y == cub->cols - 1 || (y >= last_y && y < cub->cols - 1)) && visited[x][y] == '1')
		cub->map_buffer[x][y] = '7';
	else if (visited[x][y] == '1')
		cub->map_buffer[x][y] = '8';
}

void		check_wall_direction(t_cub *cub, char **visited)
{
	int		i;
	int		j;

	i = -1;
	while (visited[++i] != NULL)
	{
		j = -1;
		while (visited[i][++j] != '\0')
			if (visited[i][j] == '1')
			parse_wall_direction(cub, visited, i, j);
	}

}

int			map_validation(t_cub *cub)
{
	char	**visited;

	if ((find_player(cub)) == -1)
		return (print_error(NO_PLAYER));
	if ((find_sprite(cub)) > 1)
		return (print_error(TOO_MANY_SP));
	if (!(visited = ft_strdup_double(cub->map_buffer)))
		return (print_error(PARSING_ERR));
	map_dfs(cub, visited, cub->player.x, cub->player.y);
	check_wall_direction(cub, visited);
	double_ptr_mem_free(visited);
	if (cub->invalid_map > 0)
		return (print_error(NOT_SURROUNDED));
	return (1);
}
