/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaekpark <jaekpark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 20:22:46 by jaekpark          #+#    #+#             */
/*   Updated: 2021/04/20 18:41:22 by jaekpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct		s_pos
{
	double			x;
	double			y;
}					t_pos;

typedef struct		s_img
{
	void			*img;
	int				*data;
	int				size_l;
	int				bpp;
	int				endian;

}					t_img;

typedef struct		s_node
{
	char			*line;
	struct s_node	*next;
}					t_node;

typedef struct		s_list
{
	struct s_node	*curr;
	struct s_node	*head;
	struct s_node	*tail;
}					t_list;

typedef struct		s_path
{
	char			*north;
	char			*south;
	char			*east;
	char			*west;
	char			*sprite;
	char			*floor;
	char			*ceil;
}					t_path;

typedef struct		s_floor
{
	double			half;
	double			row_dist;
	int				pos_y;
	int				tex_x;
	int				tex_y;
	int				ce_x;
	int				ce_y;
	t_pos			fl;
	t_pos			step;
	t_pos			ray_dir_l;
	t_pos			ray_dir_r;
}					t_floor;

typedef struct		s_raycast
{
	t_pos			ray_dir;
	t_pos			side_dist;
	t_pos			delta_dist;
	double			camera_x;
	double			perp_wall_dist;
	double			wall_x;
	double			step;
	double			tex_pos;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				tex_idx;
	int				tex_x;
	int				tex_y;
}					t_raycast;

typedef struct		s_win
{
	t_img			screen;
	t_pos			screen_size;
	int				sys_width;
	int				sys_height;
	void			*ptr;
	void			*win;
}					t_win;

typedef struct		s_tex
{
	char			*path;
	void			*img;
	int				*data;
	int				bpp;
	int				size_l;
	int				endian;
	int				width;
	int				height;
}					t_tex;

typedef struct		s_key
{
	int				w;
	int				s;
	int				a;
	int				d;
	int				q;
	int				e;
	int				esc;
}					t_key;

typedef struct		s_sprite
{
	t_pos			ray;
	t_pos			sp;
	t_pos			trans;
	double			v_mv;
	int				color;
	int				u_div;
	int				v_div;
	int				mv_screen;
	int				w;
	int				h;
	int				screen_x;
	int				start_x;
	int				start_y;
	int				end_x;
	int				end_y;
	int				tex_x;
	int				tex_y;
	double			inv;
}					t_sprite;

typedef struct		s_cub
{
	char			direction;
	int				is_map;
	int				width;
	int				height;
	int				cols;
	int				rows;
	int				save_opt;
	int				floor_color;
	int				ceiling_color;
	int				invalid_map;
	int				sprite_cnt;
	int				f_tex;
	int				c_tex;
	char			**map_buffer;
	t_pos			player;
	t_pos			sprite;
	t_list			*map;
	t_path			*path;
}					t_cub;

typedef struct		s_game
{
	t_cub			*cub;
	t_win			*window;
	t_tex			tex[8];
	t_key			key;
	t_pos			player;
	t_pos			dir;
	t_pos			plane;
	t_raycast		raycast;
	t_floor			floor;
	t_sprite		sprite;
	int				width;
	int				height;
	double			*z_buf;
	int				**buf;
	double			mv_speed;
	double			rot_speed;
}					t_game;

#endif
