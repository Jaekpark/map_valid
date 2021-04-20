/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_bmp_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 17:38:07 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/20 15:38:49 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_int(unsigned char *header, int value)
{
	int i;

	i = -1;
	while (++i < (int)sizeof(value))
	{
		header[i] = (unsigned char)(value);
		value = value >> 8;
	}
}

static void	set_short(unsigned char *header, short value)
{
	header[0] = (unsigned char)(value);
	header[1] = (unsigned char)(value >> 8);
}

static int	write_header(t_game *game, int fd, int size)
{
	int				i;
	int				width;
	int				height;
	unsigned char	header[54];

	i = 0;
	width = game->width;
	height = game->height;
	while (i < 54)
		header[i++] = (unsigned char)(0);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	set_int(header + 2, size);
	set_int(header + 10, 54);
	set_int(header + 14, 40);
	set_int(header + 18, width);
	set_int(header + 22, -height);
	set_short(header + 26, 1);
	set_short(header + 28, 24);
	set_int(header + 30, 0);
	return (write(fd, header, 54));
}

int			write_img_data(t_game *game, int fd, int pad)
{
	int		i;
	int		j;

	i = -1;
	if (!game || fd < 0)
		return (-1);
	while (++i < game->height)
	{
		j = -1;
		while (++j < game->width)
			write(fd, &game->window->screen.data[i * game->width + j], 3);
		j = -1;
		while (++j < pad)
			write(fd, "\x00", 1);
	}
	return (1);
}

int			save_bmp(t_game *game)
{
	t_win		*w;
	int			size;
	int			fd;
	int			pad;

	w = game->window;
	pad = (4 - ((int)w->screen_size.x * 3) % 4) % 4;
	size = (((int)w->screen_size.x + pad) * (int)w->screen_size.y) * 3 + 54;
	if ((fd = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
		return (print_error(BMP_OPEN_ERR));
	if (write_header(game, fd, size) != 54)
		return (print_error(BMP_HEAD_ERR));
	if (!write_img_data(game, fd, pad))
		return (print_error(BMP_DATA_ERR));
	close(fd);
	return (1);
}
