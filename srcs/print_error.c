/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 14:29:48 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/20 19:45:32 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		print_error_b(int error)
{
	if (error == TOO_MANY_SP)
		printf("Error : Invalid map. Too many sprites.\n");
	else if (error == INIT_FAIL)
		printf("Error : Initialize failed.\n");
	else if (error == TEX_EXT)
		printf("Error : Tex file was wrong.\n");
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
	else if (error == BMP_OPEN_ERR)
		printf("Error : Failed make bmp file.\n");
	else if (error == BMP_HEAD_ERR)
		printf("Error : Failed write bmp header.\n");
	else if (error == BMP_DATA_ERR)
		printf("Error : Faild write bmp data.\n");
	return (-1);
}

int		print_error(int error)
{
	if (error == NO_ARG)
		printf("Error : Argument does not exists.\n");
	else if (error == PARSING_ERR)
		printf("Error : Parsing error. Please check your '.cub' file.\n");
	else if (error == NO_PLAYER)
		printf("Error : Invalid map. Missing or more than one player.\n");
	else if (error == WRONG_NAME)
		printf("Error : Wrong file name. Please check your file name.\n");
	else if (error == WRONG_OPT)
		printf("Error : Unacceptable option. Using '--save' option.\n");
	else if (error == PARSING_ERR)
		printf("Error : Parsing error. Please check your map file.\n");
	else if (error == OPEN_ERR)
		printf("Error : Can't open file.\n");
	else if (error == NOT_SURROUNDED)
		printf("Error : Invalid map. Map isn't surrounded by walls.\n");
	else if (error == UNABLE_MAP_CHAR)
		printf("Error : Invalid map. Wrong characters in the map.\n");
	else if (error == NO_TEX)
		printf("Error : Texture file does not exists.\n");
	else if (error == TOO_MANY_ARG)
		printf("Error : Too many arguments.\n");
	else
		return (print_error_b(error));
	return (-1);
}
