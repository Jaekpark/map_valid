/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:29:48 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/18 22:48:40 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		exit_game(t_game *game)
{
	if (game)
		clear_game(game);
	exit(0);
	return (0);
}

int		print_error(int error)
{
	if (error == NO_ARG)
		printf("Error : Argument does not exists.\n");
	else if (error == PARSING_ERR)
		printf("Error : Parsing error. Please check your '.cub' file.\n");
	else if (error == NO_PLAYER)
		printf("Error : Invalid map. Can't find player.\n");
	else if (error == WRONG_NAME)
		printf("Error : Wrong file name. Please check your file name.\n");
	else if (error == WRONG_OPT)
		printf("Error : Unacceptable option. Using '--save' option.\n");
	else if (error == PARSING_ERR)
		printf("Error : Parsing error. Please check your map file.\n");
	else if (error == OPEN_ERR)
		printf("Error : Can't open file. Please check your file name or directory.\n");
	else if (error == NOT_SURROUNDED)
		printf("Error : Invalid map. Map isn't surrounded by walls.\n");
	else if (error == NO_TEX)
		printf("Error : Texture file does not exists.\n");
	else if (error == TOO_MANY_SP)
		printf("Error : Invalid map. Too many sprites.\n");
	else if (error == INIT_FAIL)
		printf("Error : Initialize failed.\n");
	else if (error == TEX_EXT)
		printf("Error : Tex file extension was wrong.\n");
	else if (error == COLOR_ERR)
		printf("Error : Floor or ceil color was wrong.\n");
	else if (error == EMPTY_MAP)
		printf("Error : Invalid map. map is empty.\n");
	else if (error == WRONG_RES)
		printf("Error : Wrong resolution. Please check your map file.\n");
	else if (error == AFTER_EMPTY)
		printf("Error : Invalid map. Empty line exist in the map.\n");
	else if (error == IDEN_IN_MAP)
		printf("Error : Identifier exist in the map.\n");
	else if (error == DOUBLE_PATH)
		printf("Error : Texture path already exist.\n");
	else if (error == UNABLE_MAP_CHAR)
		printf("Error : Invalid map. Wrong characters in the map.\n");
	return (-1);
}
