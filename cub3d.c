/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_cub3D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 16:53:58 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/20 02:28:37 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		exit_game(t_game *game)
{	
	clear_game(game);
	exit(0);
	return (0);
}

int exit_hook(t_game *game)
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

int main(int argc, char **argv)
{
	int fd;
	t_cub *cub;
	t_game *game;

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

// int	close_cub(t_cub *cub)
// {
// 	clear_cub(cub);
// 	return (-1);
// }

// int main(int argc, char **argv)
// {
// 	int fd;
// 	int ret;
// 	t_cub *cub;
// 	t_game *game;

// 	fd = 0;
// 	ret = 0;
// 	cub = NULL;
// 	game = NULL;
// 	if (!(cub = init_cub(cub)))
// 		return (print_error(INIT_FAIL));
// 	if ((fd = check_argv(argc, argv, cub)) < 3)
// 		return (close_cub(cub));
// 	if (fd >= 3)
// 	{
// 		ret = read_cub(cub, fd);
// 		printf("read_Cub after ret = %d\n", ret);
// 		if (ret != -1)
// 		{
// 			ret = map_validation(cub);
// 			printf("after map_valid ret = %d\n", ret);
// 			game = init_game(cub, game);
// 			print_cub(cub);
// 			print_game(game);
// 			set_player_dir(game, cub);
// 			init_raycast(&game->raycast);
// 			init_floor(&game->floor);
// 			load_tex(game);
// 			init_sprite(&game->sprite);

// 		}
// 	}
// 	//mlx_hook(game->window->ptr, X_EVENT_KEY_PRESS, 0, &key_press, game);
// 	//mlx_hook(game->window->ptr, X_EVENT_KEY_RELEASE, 0, &key_release, game);
// 	// img = mlx_xpm_file_to_image(game->window->ptr, "./textures/north.xpm", &width, &height);
// 	// mlx_put_image_to_window(game->window->ptr, game->window->win, game->texture[1].img, 50, 50);
// 	mlx_loop_hook(game->window->ptr, &main_loop, game);
// 	mlx_hook(game->window->win, X_EVENT_KEY_PRESS, 0, &key_press, game);
// 	mlx_hook(game->window->win, X_EVENT_KEY_RELEASE, 0, &key_release, game);
// 	mlx_loop(game->window->ptr);
// 	// if (ret == -1)
// 	// 	printf("parsing_error\n");
// 	// if (ret == -1)
// 	// 	printf("invalid map error\n");
// 	// if (ret == 0)
// 	// 	printf("normal\n");
// 	// clear_cub(cub);
// 	system("leaks cub3d > leaks_result_temp; cat leaks_result_temp | grep leaked && rm -rf leaks_result_temp");
// 	return (0);
// }
