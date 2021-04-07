#include "cub3d.h"

int main(int argc, char **argv)
{
	int i;
	int fx;
	int fy;
	int ret;
	t_cub *cub;

	i = 0;
	fx = 0;
	fy = 0;
	cub = NULL;
	if (argc <= 1)
		printf("\n");
	cub = init_cub(cub);
	ret = read_cub(argv, cub);
	if (ret == -1)
		printf("parsing_error\n");
	ret = map_validation(cub);
	if (ret == -1)
		printf("invalid map error\n");
	if (ret == 0)
		printf("normal\n");
	clear_cub(cub);
	//system("leaks cub3d > leaks_result_temp; cat leaks_result_temp | grep leaked && rm -rf leaks_result_temp");
	return (0);
}
