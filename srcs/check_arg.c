/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 18:17:15 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/20 20:22:24 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_file_open(char *path)
{
	int	fd;

	fd = 0;
	if ((fd = open(path, O_RDONLY)) < 0)
		return (-1);
	else if (fd >= 3)
		close(fd);
	return (1);
}

int		check_file_name(const char *file_name)
{
	int	pos;

	pos = 0;
	if (!file_name)
		return (-1);
	if (ft_strlen((char *)file_name) < 5)
		return (-1);
	pos = ft_strlen((char *)file_name) - 4;
	while (pos--)
		file_name++;
	return (ft_strcmp((char *)file_name, MAP_EXTENSION));
}

int		check_file_extension(char *file, char *extension)
{
	int	pos;

	pos = 0;
	if (!file || !extension)
		return (-1);
	if (ft_strlen(file) <= ft_strlen(extension))
		return (-1);
	pos = ft_strlen(file) - ft_strlen(extension);
	while (pos--)
		file++;
	return (ft_strcmp(file, extension));
}

int		check_option(const char *option)
{
	if (!option)
		return (-1);
	if (ft_strlen((char *)option) != ft_strlen(SAVE))
		return (-1);
	return (ft_strcmp((char *)option, SAVE));
}

int		check_argv(int argc, char **argv, t_cub *cub)
{
	int	fd;

	fd = 0;
	if (argc < 2)
		return (print_error(NO_ARG));
	if (argc > 3)
		return (print_error(TOO_MANY_ARG));
	else if (argc >= 2)
	{
		if (check_file_name(argv[1]) != 0)
			return (print_error(WRONG_NAME));
		if ((fd = open(argv[1], O_RDONLY)) < 0)
			return (print_error(OPEN_ERR));
		if (argc == 3)
		{
			if (check_option(argv[2]) != 0)
				return (print_error(WRONG_OPT));
			else if ((check_option(argv[2])) == 0)
				cub->save_opt = 1;
		}
	}
	return (fd);
}
