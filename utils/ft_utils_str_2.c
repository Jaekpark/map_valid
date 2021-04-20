/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_str_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:18:40 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/20 16:19:24 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1[i] == '\0' && s2[i] == '\0')
		return (-1);
	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int			ft_strncmp(char *s1, char *s2, int num)
{
	int	i;

	i = 0;
	if (s1[i] == '\0' && s2[i] != '\0')
		return (-1);
	while (s1[i] && i < num)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char		**ft_strdup_double(char **s)
{
	int		x;
	char	**ret;

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

void		double_ptr_mem_free(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}
