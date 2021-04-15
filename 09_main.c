/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 16:08:46 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/15 16:08:47 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		set_default_config(t_game *game, t_cub *cub, int fd)
{
	int ret;

	ret = 0;
	if (fd >= 3)
	{
		if ((ret = read_cub(cub, fd)) == -1)
			return (close_cub(cub));
		if ((ret = map_validation(cub)) == -1)
			return (close_cub(cub));
		if (!(game = init_game(game)))
			return (close_cub(cub));
		set_player_dir(game, cub);
		init_raycast(&game->raycast);
		init_floor(&game_floor);
		init_sprite(&game->sprite);
		load_texture(game);
	}

}