#include "cub3d.h"

int main(int argc, char **argv)
{
	int fd;
	int ret;
	t_cub *cub;
	t_game *game;

	fd = 0;
	ret = 0;
	cub = NULL;
	game = NULL;
	cub = init_cub(cub);
	fd = check_argv(argc, argv, cub);
	
	printf("fd = %d\n", fd);
	printf("save_opt = %d\n", cub->save_opt);
	if (fd >= 3)
	{
		ret = read_cub(cub, fd);
		printf("read_Cub after ret = %d\n", ret);
		if (ret != -1)
		{
			ret = map_validation(cub);
			game = init_game(cub, game);
			set_player_dir(game, cub);
			init_raycast(&game->raycast);
			init_floor(&game->floor);
			load_texture(game);
			print_cub(cub);
			print_game(game);
		}
	}
	//mlx_hook(game->window->ptr, X_EVENT_KEY_PRESS, 0, &key_press, game);
	//mlx_hook(game->window->ptr, X_EVENT_KEY_RELEASE, 0, &key_release, game);
	// img = mlx_xpm_file_to_image(game->window->ptr, "./textures/north.xpm", &width, &height);
	// mlx_put_image_to_window(game->window->ptr, game->window->win, game->texture[1].img, 50, 50);
	mlx_loop_hook(game->window->ptr, &main_loop, game);
	mlx_hook(game->window->win, X_EVENT_KEY_PRESS, 0, &key_press, game);
	mlx_hook(game->window->win, X_EVENT_KEY_RELEASE, 0, &key_release, game);
	mlx_loop(game->window->ptr);
	// if (ret == -1)
	// 	printf("parsing_error\n");
	// if (ret == -1)
	// 	printf("invalid map error\n");
	// if (ret == 0)
	// 	printf("normal\n");
	// clear_cub(cub);
	//system("leaks cub3d > leaks_result_temp; cat leaks_result_temp | grep leaked && rm -rf leaks_result_temp");
	return (0);
}
