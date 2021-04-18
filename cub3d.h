#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include "./struct.h"
#include "./constant.h"
#include "./mlx/mlx.h"
#include "./mlxbeta/mlxbeta.h"

// set_game
int		set_default_config(t_game *game, t_cub *cub, int fd);
void	set_player_dir(t_game *game, t_cub *cub);
void	set_screen_buf(t_game *game);
void	set_pos(t_pos *pos, double x, double y);
void	set_screen_size(t_cub *cub, t_win *win);

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

int		exit_game(t_game *game);
int		exit_hook(t_game *game);
// gnl
int		get_next_line(int fd, char **line);

// split
char	**ft_split(char const *s, char c);
void	double_ptr_mem_free(char **str);

// check
int		check_tex_file(t_game *game);
int		check_color_exist(t_cub *cub);
int		check_path_exist(t_cub *cub);
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
