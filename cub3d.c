/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 16:53:58 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/20 20:25:06 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		exit_game(t_game *game)
{
	clear_game(game);
	exit(0);
	return (0);
}

int		exit_hook(t_game *game)
{
	return (exit_game(game));
}

void	config_game(t_cub *cub, t_game *game)
{
	if (!cub || !game)
		return ;
	load_tex(game);
	set_player_dir(game, cub);
	init_raycast(&game->raycast);
	init_floor(&game->floor);
	init_sprite(&game->sprite);
	if (cub->save_opt == 1)
		make_bmp(game);
}

int		parse_game(t_cub *cub, int fd)
{
	int ret;

	ret = 0;
	if ((ret = read_cub(cub, fd)) == -1)
		return (-1);
	if ((ret = map_validation(cub)) == -1)
		return (-1);
	if ((ret = check_path_exist(cub)) == -1)
		return (-1);
	if ((ret = check_color_exist(cub)) == -1)
		return (-1);
	return (ret);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_cub	*cub;
	t_game	*game;

	fd = 0;
	cub = NULL;
	game = NULL;
	cub = init_cub(cub);
	if ((fd = check_argv(argc, argv, cub)) < 3)
		return (clear_cub(cub));
	if (fd >= 3)
	{
		if (parse_game(cub, fd) == -1)
			return (clear_cub(cub));
		if (!(game = init_game(cub, game)))
			return (clear_cub(cub));
		config_game(cub, game);
	}
	mlx_loop_hook(game->window->ptr, &main_loop, game);
	mlx_hook(game->window->win, X_EVENT_KEY_PRESS, 0, &key_press, game);
	mlx_hook(game->window->win, X_EVENT_KEY_RELEASE, 0, &key_release, game);
	mlx_hook(game->window->win, X_EVENT_KEY_EXIT, 0, &exit_hook, game);
	mlx_loop(game->window->ptr);
	return (0);
}
