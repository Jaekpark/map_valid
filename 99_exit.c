/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   99_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 20:19:37 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/18 20:54:28 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_cub(t_cub *cub)
{
	printf("close cub\n");
	clear_cub(cub);
	return (-1);
}

int exit_hook(t_game *game)
{
	return (exit_game(game));
}
