/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 11:35:54 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/20 16:05:48 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		map_dfs(t_cub *cub, char **v, int x, int y)
{
	if (x == 0 || y == cub->cols - 1 || x == cub->rows - 1 || y == 0)
	{
		cub->invalid_map += 1;
		return ;
	}
	if (v[x][y] == '0' || ft_isplayer(v[x][y]) || v[x][y] == ' ')
		v[x][y] = 'V';
	if (x < cub->rows - 1 && (v[x + 1][y] == '0' || v[x + 1][y] == ' '))
		map_dfs(cub, v, x + 1, y);
	if (x != 0 && (v[x - 1][y] == '0' || v[x - 1][y] == ' '))
		map_dfs(cub, v, x - 1, y);
	if (y < cub->cols - 1 && (v[x][y + 1] == '0' || v[x][y + 1] == ' '))
		map_dfs(cub, v, x, y + 1);
	if (y != 0 && (v[x][y - 1] == '0' || v[x][y - 1] == ' '))
		map_dfs(cub, v, x, y - 1);
}

void		parse_wall_direction(t_cub *cub, char **v, int x, int y)
{
	int		q_x;
	int		q_y;
	int		after_sp;
	int		before_sp;
	int		last_y;

	q_x = cub->rows / 4;
	q_y = cub->cols / 4;
	after_sp = after_space(v);
	before_sp = before_space(v);
	last_y = cub->cols - 1 - after_sp;
	if (x == 0 && v[x][y] == '1')
		cub->map_buffer[x][y] = '4';
	else if (x == cub->rows - 1 && v[x][y] == '1')
		cub->map_buffer[x][y] = '5';
	else if (((y == 0) || (y < last_y && y <= before_sp)) && v[x][y] == '1')
		cub->map_buffer[x][y] = '6';
	else if ((y == cub->cols - 1 || (y >= last_y && y < cub->cols - 1))
			&& v[x][y] == '1')
		cub->map_buffer[x][y] = '7';
	else if (v[x][y] == '1')
		cub->map_buffer[x][y] = '8';
}

void		check_wall_direction(t_cub *cub, char **v)
{
	int		i;
	int		j;

	i = -1;
	while (v[++i] != NULL)
	{
		j = -1;
		while (v[i][++j] != '\0')
			if (v[i][j] == '1')
				parse_wall_direction(cub, v, i, j);
	}
}

int			map_validation(t_cub *cub)
{
	char	**v;

	if ((find_player(cub)) == -1)
		return (print_error(NO_PLAYER));
	if ((find_sprite(cub)) > 1)
		return (print_error(TOO_MANY_SP));
	if (!(v = ft_strdup_double(cub->map_buffer)))
		return (print_error(PARSING_ERR));
	map_dfs(cub, v, cub->player.x, cub->player.y);
	check_wall_direction(cub, v);
	double_ptr_mem_free(v);
	if (cub->invalid_map > 0)
		return (print_error(NOT_SURROUNDED));
	return (1);
}
