/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constant.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 20:22:38 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/20 19:43:49 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANT_H
# define CONSTANT_H

# define MAP_EXTENSION ".cub"
# define TEX_EXTENSION ".xpm"
# define VALID_CHAR " 012NSEW"
# define SAVE "--save"
# define DIRECTION "NSEW"
# define MID_WALL_PATH "./textures/mid_wall.xpm"
# define D_RATIO 0.5625

# define OPEN_MAX 32
# define BUFFER_SIZE 128

# define NO_ARG 100
# define WRONG_NAME 101
# define WRONG_OPT 102
# define PARSING_ERR 103
# define OPEN_ERR 104
# define COLOR_ERR 105
# define NO_PLAYER 106
# define NOT_SURROUNDED 107
# define NO_TEX 108
# define TOO_MANY_SP 109
# define INIT_FAIL 110
# define TEX_EXT 111
# define EMPTY_MAP 112
# define WRONG_RES 113
# define AFTER_EMPTY 114
# define IDEN_IN_MAP 115
# define DOUBLE_PATH 116
# define UNABLE_MAP_CHAR 117
# define BMP_OPEN_ERR 118
# define BMP_HEAD_ERR 119
# define BMP_DATA_ERR 120
# define TOO_MANY_ARG 121

# define N_TEX 0
# define S_TEX 1
# define W_TEX 2
# define E_TEX 3
# define M_TEX 4
# define SP_TEX 5
# define FL_TEX 6
# define CE_TEX 7
# define FL_COL 8
# define CE_COL 9
# define RESOLUTION 10
# define EMPTY_LINE 11
# define MAP_LINE 12

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_KEY_EXIT 17

# define KEY_W 13
# define KEY_S 1
# define KEY_D 2
# define KEY_A 0
# define KEY_ESC 53
# define KEY_SP 49
# define KEY_TAB 48
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_LEFT 123
# define KEY_Q 12
# define KEY_E 14

#endif
