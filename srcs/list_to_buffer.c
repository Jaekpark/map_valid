/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_list_to_buffer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 11:37:52 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/19 15:23:03 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char		*make_blank_str(int count)
{
	int		i;
	char	*blank;

	i = 0;
	if (!(blank = malloc(sizeof(char) * (count + 1))))
		return (NULL);
	while (i < count)
	{
		blank[i] = ' ';
		i++;
	}
	blank[i] = '\0';
	return (blank);
}

int			calc_base_width(char **map_buffer)
{
	int		i;
	int		j;
	int		width;

	i = 0;
	width = 0;
	while (map_buffer[i] != NULL)
	{
		j = 0;
		while (map_buffer[i][j] != '\0')
			j++;
		if (width < j)
			width = j;
		i++;
	}
	return (width);
}

void		make_map_buffer(t_cub *cub)
{
	int		i;
	int		count;
	char	*blank;

	i = 0;
	count = 0;
	while (cub->map_buffer[i] != NULL)
	{
		count = cub->cols - ft_strlen(cub->map_buffer[i]);
		if (count > 0)
		{
			blank = make_blank_str(count);
			cub->map_buffer[i] = ft_strjoin(cub->map_buffer[i], blank);
			free(blank);
		}
		i++;
	}
}

int			list_to_buffer(t_cub *cub)
{
	int		i;
	int		size;
	char	**temp;
	t_node	*map_temp;

	if (!(map_temp = cub->map->head))
		return (-1);
	i = 0;
	size = ft_lstsize(cub->map);
	if (!(temp = malloc(sizeof(char *) * (size + 1))))
		return (print_error(PARSING_ERR));
	while (map_temp != NULL)
	{
		temp[i++] = ft_strdup(map_temp->line);
		map_temp = map_temp->next;
	}
	temp[i] = NULL;
	cub->map_buffer = temp;
	cub->cols = calc_base_width(cub->map_buffer);
	cub->rows = size;
	make_map_buffer(cub);
	return (1);
}
