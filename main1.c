#include "cub3d.h"

int main(int argc, char **argv)
{
	int i;
	int fx;
	int fy;
	int ret;
	t_cub *cub;
	t_game *game;

	i = 0;
	fx = 0;
	fy = 0;
	cub = NULL;
	game = NULL;
	if (argc <= 1)
		printf("\n");
	cub = init_cub(cub);
	ret = check_argv(argc, argv, cub);
	printf("ret = %d\n", ret);
	printf("save_opt = %d\n", cub->save_opt);
	if (ret != -1)
	{
		ret = read_cub(argv, cub);
		ret = map_validation(cub);
		game = init_game(cub, game);
	}
	//printf("cub width height = %d %d\n", cub->width, cub->height);
	//printf(" screen size %f %f\n", game->window->screen_size.x, game->window->screen_size.y);
	if (ret == -1)
		printf("parsing_error\n");
	if (ret == -1)
		printf("invalid map error\n");
	if (ret == 0)
		printf("normal\n");
	clear_cub(cub);
	//system("leaks cub3d > leaks_result_temp; cat leaks_result_temp | grep leaked && rm -rf leaks_result_temp");
	return (0);
}
