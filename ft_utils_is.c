/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_is.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:31:13 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/06 15:42:01 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
int		ft_isplayer(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (-1);
}
int		ft_ismap(char *line)
{
	if (line[0] == 0)
		return (-1);
	while (*line)
	{
		if (!ft_strchr(VALID_CHAR, *line))
			return (-1);
		line++;
	}
	return (1);
}

int		ft_isalpha(char c)
{
	if ((c >= 65 && c <= 90) || (c >=97 && c <= 122))
		return (1);
	return (-1);
}

int		ft_isnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (-1);
}
