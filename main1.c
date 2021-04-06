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
	validation(cub);
	clear_cub(cub);
	//system("leaks cub3d > leaks_result_temp; cat leaks_result_temp | grep leaked && rm -rf leaks_result_temp");

	return (0);
}
