/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_map_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 11:35:54 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/06 15:50:58 by jaekpark         ###   ########.fr       */
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
		printf("str[%d] = |%s|\n", i, s[i]);
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

int		find_player(t_cub *cub)
{
	int x;
	int y;

	x = 0;
	while(cub->map_buffer[x] != NULL)
	{
		y = 0;
		while (cub->map_buffer[x][y] != '\0')
		{
			if (cub->map_buffer[x][y] == 'N' || cub->map_buffer[x][y] == 'E')
			{
				cub->player.pos_x = x;
				cub->player.pos_y = y;
				return (1);
			}
			else if (cub->map_buffer[x][y] == 'W' || cub->map_buffer[x][y] == 'S')
			{
				cub->player.pos_x = x;
				cub->player.pos_y = y;
				return (1);
			}
			y++;
		}
		x++;
	}
	return (-1);
}
int 	map_valid(t_cub *cub, char **visited, int x, int y)
{
	printf("!\n");
	if (x == 0 || y == cub->cols - 1 || x == cub->rows - 1 || y == 0)
		return (-1);
	else if (visited[x][y] != '0' && ft_isplayer(visited[x][y]) == -1)
		return (-1);
	if (visited[x][y] == '0')
		visited[x][y] = 'V';
	if (x < cub->rows - 1 && visited[x + 1][y] == '0')
		map_valid(cub, visited, x + 1, y);
	if (x != 0 && visited[x - 1][y] == '0')
		map_valid(cub, visited, x, y);
	if (y < cub->cols - 1 && visited[x][y + 1] == '0')
		map_valid(cub, visited, x, y + 1);
	if (y != 0 && visited[x][y - 1] == '0')
		map_valid(cub, visited, x, y - 1);
	return (1);
}

int		validation(t_cub *cub)
{
	int ret;
	char **visited;

	ret = 0;
	visited = ft_strdup_double(cub->map_buffer);
	print_double_ptr(visited);
	if (!(find_player(cub)))
		return (-1);
	printf(" find player x = %d, y = %d\n", cub->player.pos_x, cub->player.pos_y);
	ret = map_valid(cub, visited, cub->player.pos_x, cub->player.pos_y);
	print_double_ptr(visited);
	return (1);
}