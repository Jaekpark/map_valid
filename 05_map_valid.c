/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_map_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 11:35:54 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/14 17:53:40 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int map_rows(char **map)
{
	int i;

	i = 0;
	while (map[i] != NULL)
		i++;
	return (i);
}

void	print_double_ptr(char **s)
{
	int i;

	i = -1;
	while (s[++i] != NULL)
		printf("str[%2d] = |%s|\n", i, s[i]);
}

char	**ft_strdup_double(char **s)
{
	int x;
	char **ret;

	x = map_rows(s);
	if (!(ret = malloc(sizeof(char *) * (x + 1))))
		return (NULL);
	x = 0;
	while (s[x] != NULL)
	{
		ret[x] = ft_strdup(s[x]);
		x++;
	}
	ret[x] = NULL;
	return (ret);
}

int		find_sprite(t_cub *cub)
{
	int x;
	int y;
	int	find;

	x = 0;
	find = 0;
	while(cub->map_buffer[x] != NULL)
	{
		y = 0;
		while (cub->map_buffer[x][y] != '\0')
		{
			if (cub->map_buffer[x][y] == '2')
			{
				if (find == 0)
				{
					cub->sprite.x = x + 0.5;
					cub->sprite.y = y + 0.5;
					find = 1;
				}
				else if (find == 1)
					return (-1);
			}
			y++;
		}
		x++;
	}
	return (1);	
}

int		find_player(t_cub *cub)
{
	int x;
	int y;
	int	find;

	x = 0;
	find = 0;
	while(cub->map_buffer[x] != NULL)
	{
		y = 0;
		while (cub->map_buffer[x][y] != '\0')
		{
			if (ft_strchr(DIRECTION, cub->map_buffer[x][y]))
			{
				if (find == 0)
				{
					cub->player.x = x;
					cub->player.y = y;
					cub->direction = cub->map_buffer[x][y];
					cub->map_buffer[x][y] = '0';
					find = 1;
				}
				else if (find == 1)
					return (-1);
			}
			y++;
		}
		x++;
	}
	return (1);
}

void	set_player_dir(t_game *game, t_cub *cub)
{
	if (cub->direction == 'N')
	{
		set_pos(&game->dir, -1, 0);
		set_pos(&game->plane, 0, 0.66);
	}
	else if (cub->direction == 'S')
	{
		set_pos(&game->dir, 1, 0);
		set_pos(&game->plane, 0, -0.66);
	}	
	else if (cub->direction == 'E')
	{
		set_pos(&game->dir, 0, 1);
		set_pos(&game->plane, 0.66, 0);
	}
	else if (cub->direction == 'W')
	{
		set_pos(&game->dir, 0, -1);
		set_pos(&game->plane, -0.66, 0);
	}
}

void 	map_dfs(t_cub *cub, char **visited, int x, int y)
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
int		is_sidewall(t_cub *cub, char **visited, int x, int y)
{
	int space;

	space = 0;
	if (y < cub->cols - 1 && visited[x][y + 1] == 'V')
		space++;
	if (y != 0 && visited[x][y - 1] == 'V')
		space++;
	if (x < cub->rows - 1 && visited[x + 1][y] == 'V')
		space++;
	if (x != 0 && visited[x - 1][y] == 'V')
		space++;
	return (space);
}

void	wall_dir(t_cub *cub, char **visited, int x, int y)
{
	int space;

	space = is_sidewall(cub, visited, x, y);
	if (x == 0 && visited[x][y] == '1')
		visited[x][y] = 'N';
	else if (x == cub->rows - 1 && visited[x][y] == '1')
		visited[x][y] = 'S';
	else if (y == 0 && visited[x][y] == '1')
		visited[x][y] = 'E';
	else if (y == cub->cols - 1 && visited[x][y] == '1')
		visited[x][y] = 'W';
	else if (space == 1 && x != 0 && visited[x - 1][y] == 'V')
		visited[x][y] = 'S';
	else if (space == 1 && x < cub->rows - 1 && visited[x + 1][y] == 'V')
		visited[x][y] = 'N';
	else if (space == 1 && y < cub->cols - 1 && visited[x][y + 1] == 'V')
		visited[x][y] = 'W';
	else if (space == 1 && y != 0 && visited[x][y - 1] == 'V')
		visited[x][y] = 'E';
}

void 	wall_direction(t_cub *cub, char **visited)
{
	int i;
	int j;

	i = -1;
	while (visited[++i] != NULL)
	{
		j = -1;
		while (visited[i][++j] != '\0')
			if (visited[i][j] == '1')
			wall_dir(cub, visited, i, j);
	}

}

int		map_validation(t_cub *cub)
{
	char **visited;

	if (!(find_player(cub)))
		return (print_error(NO_PLAYER));
	if (!(find_sprite(cub)))
		return (print_error(TOO_MANY_SP));
	if (!(visited = ft_strdup_double(cub->map_buffer)))
		return (print_error(PARSING_ERR));
	map_dfs(cub, visited, cub->player.x, cub->player.y);
	double_ptr_mem_free(visited);
	if (cub->invalid_map > 0)
		return (print_error(NOT_SURROUNDED));
	return (1);
}
