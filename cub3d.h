#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include "./mlx/mlx.h"

# define MAP_EXTENSION ".cub"
# define TEX_EXTENSION ".xpm"
# define VALID_CHAR " 012NSEW"
# define SAVE "--save"
# define DIRECTION "NSEW"

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

# define N_TEX 0
# define S_TEX 1
# define E_TEX 2
# define W_TEX 3
# define SP_TEX 4
# define FL_TEX 5
# define CE_TEX 6
# define FL_COL 7
# define CE_COL 8
# define RESOLUTION 9
# define EMPTY_LINE 10
# define MAP_LINE 11

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

typedef struct s_pos
{
	double	x;
	double 	y;
}			t_pos;

typedef struct	s_img
{
	void	*img;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;

}				t_img;

typedef struct s_node
{
	char	*line;
	struct s_node *next;
}				t_node;

typedef struct s_list
{
	struct s_node *curr;
	struct s_node *head;
	struct s_node *tail;
}	t_list;

typedef struct s_path
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*sprite;
	char	*floor;
	char	*ceil;
}	t_path;

typedef struct s_floor
{
	double half;
	double row_dist;
	int pos_y;
	int tex_x;
	int tex_y;
	int ce_x;
	int ce_y;
	t_pos fl;
	t_pos step;
	t_pos ray_dir_l;
	t_pos ray_dir_r;
}	t_floor;

typedef struct s_raycast
{
	double camera_x;
	double perp_wall_dist;
	int hit;
	int side;
	int	line_height;
	int draw_start;
	int draw_end;
	int	map_x;
	int map_y;
	int step_x;
	int step_y;
	int tex_idx;
	double wall_x;
	int tex_x;
	int tex_y;
	double step;
	double tex_pos;
	t_pos ray_dir;
	t_pos side_dist;
	t_pos delta_dist;
}		t_raycast;

typedef struct s_win
{
	t_img screen;
	t_pos screen_size;
	void *ptr;
	void *win;
}			t_win;

typedef struct s_tex
{
	void	*img;
	int		*data;
	int		bpp;
	int		size_l;
	int		endian;
	int		width;
	int		height;
}			t_tex;

typedef struct s_key
{
	int w;
	int s;
	int a;
	int d;
	int esc;
}	t_key;

typedef struct s_sprite
{
	t_pos ray;
	t_pos sp;
	t_pos trans;
	double v_mv;
	int u_div;
	int v_div;
	int v_mv_screen;
	int sp_width;
	int sp_height;
	int	screen_x;
	int start_x;
	int start_y;
	int end_x;
	int end_y;
	int tex_x;
	int tex_y;
	double inv;
	
}	t_sprite;

typedef struct	s_cub
{
	char	direction;
	int is_map;
	int width;
	int height;
	int cols;
	int rows;
	int	save_opt;
	int floor_color;
	int ceiling_color;
	int	invalid_map;
	int sprite_cnt;
	char **map_buffer;
	t_pos	player;
	t_pos	sprite;
	t_list	*map;
	t_path	*base_path;
	t_path	*path;
}	t_cub;
typedef struct 	s_game
{
	t_cub *cub;
	t_win *window;
	t_tex tex[7];
	t_key key;
	t_pos player;;
	t_pos dir;
	t_pos plane;
	t_raycast raycast;
	t_floor floor;
	t_sprite sprite;
	int width;
	int height;
	double *z_buf;
	int	**buf;
	double mv_speed;
	double rot_speed;
}	t_game;

// set_game
int		set_default_config(t_game *game, t_cub *cub, int fd);
void	set_player_dir(t_game *game, t_cub *cub);
void	set_screen_buf(t_game *game);
void	set_pos(t_pos *pos, double x, double y);
int		set_screen_size(t_cub *cub, t_pos *screen_size);

// set_raycast_param
void	set_sprite_ray(t_game *game, t_sprite *item);
void	set_floor_ray(t_game *game, t_floor *floor, int y);
void	set_wall_ray(t_game *game, t_raycast *raycast, int x);
void	set_side_dist(t_game *game, t_raycast *raycast);
void	set_draw_wall_param(t_game *game, t_raycast *raycast);

// run_casting
void	calc(t_game *game);
void	draw(t_game *game);
int		main_loop(t_game *game);

//close
int		close_cub(t_cub *cub);

// print
void	print_path(t_path *path);
void	print_game(t_game *game);
void	print_node(t_list *list);
void	print_cub(t_cub *cub);

//ray_cast
void	coord_tex(t_game *game, t_raycast *raycast, int x);
void	dda(t_game *game, t_raycast *raycast);
void	sprite_casting(t_game *game, t_sprite *item, int stripe);
void	floor_casting(t_game *game, t_floor *floor, int x, int y);
void	wall_casting(t_game *game, int x);

// key
int		key_release(int key, t_game *game);
int		key_press(int key, t_game *game);
void	key_update(t_game *game);
void	rot_right_left(t_game *game);
void	mv_forward_back(t_game *game, char **map_buffer);

// load_texture
void	load_tex(t_game *game);
void	load_tex_img(t_game *game, t_tex *tex, char *path);

// list_to_buffer
int		list_to_buffer(t_cub *cub);
char	*make_blank(int count);
int		set_base_width(char **map_buffer);
void	make_map_buffer(t_cub *cub);

// map_valid
void	map_dfs(t_cub *cub, char **visited, int x, int y);
int		find_player(t_cub *cub);
int		map_rows(char **map);
int		map_validation(t_cub *cub);
char	**ft_strdup_double(char **s);
void	print_double_ptr(char **s);
void	set_player_dir(t_game *game, t_cub *cub);

// read

int		read_cub(t_cub *cub, int fd);
int		parse_line(t_cub *cub, char *line, int eof);

// ft_is~
int		ft_ismap(char *line);
int		ft_isalpha(char c);
int		ft_isnum(char c);
int		map_rows(char **map);
int		ft_isplayer(char c);

// ft_atoi
int		ft_atoi(const char *str);

// ft_str~
char	*ft_strdup(char *s1);
int		ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *s, int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int num);
char	**ft_strdup_dobule(char **s);
int		ft_strlcpy(char *dest, const char *src, int dstsize);

// gnl
int		get_next_line(int fd, char **line);

// split
char	**ft_split(char const *s, char c);
void	double_ptr_mem_free(char **str);

// check
int		check_file_name(const char *file_name);
int		check_option(const char *option);
int		check_identifier(char *line);
int		check_file_extension(char *file, char *extension);
int		check_argv(int argc, char **argv, t_cub *cub);

// error
int		print_error(int error);

// init
t_list	*init_list(t_list *list);
t_cub	*init_cub(t_cub *cub);
t_path	*init_tex(t_path *path);
t_win	*init_window(t_cub *cub, t_win *window);
t_game	*init_game(t_cub *cub, t_game *game);
void	init_raycast(t_raycast *raycast);
void	init_floor(t_floor *floor);
void	init_sprite(t_sprite *sprite);

// parsing
int		parsing_path(t_cub *cub, char *line, int index);
int		parsing_color(t_cub *cub, char *line, int index);
int		parsing_resolution(t_cub *cub, char *line);
int		parsing_map(t_cub *cub, char *line);
int		check_resolution (char *line);
int		check_color_space(char *line);
int		check_color_char(char *line);
int		make_color(char **color);

// clear
void	clear_map(t_list *map);
void	clear_path(t_path *path);
void	clear_cub(t_cub *cub);
void	clear_map_buffer(char **map_buffer);
void	clear_window(t_win *window);
void	clear_game(t_game *game);
void	clear_buf(t_game *game);

// lst
int		ft_lstsize(t_list *map);

#endif
