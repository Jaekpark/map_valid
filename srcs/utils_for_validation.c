/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_validation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:30:18 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/20 15:56:18 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		map_rows(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
		i++;
	return (i);
}

int		find_sprite(t_cub *cub)
{
	int	x;
	int	y;

	x = -1;
	while (cub->map_buffer[++x] != NULL)
	{
		y = -1;
		while (cub->map_buffer[x][++y] != '\0')
		{
			if (cub->map_buffer[x][y] == '2')
			{
				if (cub->sprite_cnt == 0)
				{
					cub->sprite.x = x + 0.5;
					cub->sprite.y = y + 0.5;
					cub->sprite_cnt = 1;
				}
				else if (cub->sprite_cnt > 0)
					cub->sprite_cnt++;
			}
		}
	}
	return (cub->sprite_cnt);
}

int		find_player(t_cub *cub)
{
	int	x;
	int	y;
	int	find;

	x = -1;
	find = 0;
	while (cub->map_buffer[++x] != NULL)
	{
		y = -1;
		while (cub->map_buffer[x][++y] != '\0')
		{
			if (ft_strchr(DIRECTION, cub->map_buffer[x][y]))
			{
				cub->player.x = x;
				cub->player.y = y;
				cub->direction = cub->map_buffer[x][y];
				cub->map_buffer[x][y] = '0';
				find++;
			}
		}
	}
	if (find != 1)
		return (-1);
	return (1);
}

int		before_space(char **visited)
{
	int	x;
	int	y;
	int	ret;
	int	space;

	x = -1;
	ret = 0;
	while (visited[++x] != NULL)
	{
		y = -1;
		space = 0;
		while (visited[x][++y] == ' ')
			space++;
		if (ret <= space)
			ret = space;
	}
	return (ret);
}

int		after_space(char **visited)
{
	int x;
	int y;
	int ret;
	int space;

	x = -1;
	ret = 0;
	while (visited[++x] != NULL)
	{
		y = ft_strlen(visited[x]) - 1;
		space = 0;
		while (visited[x][y] == ' ')
		{
			y--;
			space++;
		}
		if (ret <= space)
			ret = space;
	}
	return (ret);
}
