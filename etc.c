// int		check_tex_file(t_game *game)
// {
// 	int i;
// 	int fd;

// 	i = 0;
// 	fd = 0;
// 	while (i <= CE_TEX)
// 	{
// 		if (!(fd = open(game->tex[i].path, O_RDONLY)))
// 			return (print_error(NO_TEX));
// 		else if (fd >= 3)
// 			close(fd);
// 		i++;
// 	}
// 	return (1);
// }


int		is_sidewall(t_cub *cub, char **visited, int x, int y)
{
	int space;

	space = 0;
	if (y < cub->cols - 1 && visited[x][y + 1] == 'V')
		space++;
	if (y != 0 && visited[x][y - 1] == 'V')
		space++;
	if (x < cub->rows - 1 && visited[x + 1][y] == 'V')
		space++;
	if (x != 0 && visited[x - 1][y] == 'V')
		space++;
	return (space);
}