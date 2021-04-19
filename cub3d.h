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

// 00_main.c
int		exit_game(t_game *game);
int		exit_hook(t_game *game);
void	config_game(t_cub *cub, t_game *game);
int		parse_game(t_cub *cub, int fd);

// 00_key_handle.c
void	mv_forward_back(t_game *game, char **map_buffer);
void	rot_right_left(t_game *game);
void	key_update(t_game *game);
int		key_press(int key, t_game *game);
int		key_release(int key, t_game *game);

// 01_check_arg.c
int		check_file_open(char *path);
int		check_file_name(const char *file_name);
int		check_file_extension(char *file, char *extension);
int		check_option(const char *option);
int		check_argv(int argc, char **argv, t_cub *cub);

// 01_check_map_file_1.c
int		is_tex(char *line);
int		check_path_exist(t_cub *cub);
int		check_identifier(char *line);
int		check_resolution(char *line);

// 01_check_map_file_2.c
int		check_color_exist(t_cub *cub);
int		check_color_space(char *line);
int		check_color_char(char *line);
int		check_color_overlap(t_cub *cub, int index);

// 02_error.c
int		print_error(int error);
int		print_error_b(int error);

// 03_init_for_raycasting.c
void	init_floor(t_floor *floor);
void	init_raycast(t_raycast *raycast);
void	init_sprite(t_sprite *sprite);
void	init_key(t_key *key);

// 03_init_for_parsing.c
t_list	*init_list(t_list *list);
t_path	*init_tex(t_path *path);
t_cub	*init_cub(t_cub *cub);
t_win	*init_win(t_cub *cub, t_win *window);
t_game	*init_game(t_cub *cub, t_game *game);

// 03_setup_for_game.c
void	set_pos(t_pos *pos, double x, double y);
void	set_player_dir(t_game *game, t_cub *cub);
void	set_screen_buf(t_game *game);
void	set_screen_size(t_cub *cub, t_win *window);

// 04_read_map_file.c
int		put_path(char **dest, char *src);
int		read_cub(t_cub *cub, int fd);
int		parse_line(t_cub *cub, char *line, int eof);

// 05_parse_map_file.c
int		parsing_path(t_cub *cub, char *line, int index);
int		make_color(char **color);
int		parsing_color(t_cub *cub, char *line, int index);
int		parsing_resolution(t_cub *cub, char *line);
int		parsing_map(t_cub *cub, char *line);

// 06_list_to_buffer.c
char	*make_blank_str(int count);
void	make_map_buffer(t_cub *cub);
int		calc_base_width(char **map_buffer);
int		list_to_buffer(t_cub *cub);

// 07_valid_map_buffer.c
void	map_dfs(t_cub *cub, char **visited, int x, int y);
void	parse_wall_direction(t_cub *cub, char **visited, int x, int y);
void	check_wall_direction(t_cub *cub, char **visitied);
int		map_validation(t_cub *cub);

// 07_valid_map_utils.c
int		map_rows(char **map);
int		find_sprite(t_cub *cub);
int		find_player(t_cub *cub);
int		before_space(char **visited);
int		after_space(char **visited);

// 08_load_texture_file.c
void	load_tex_img(t_game *game, t_tex *tex, char *path);
void	load_tex(t_game *game);

// 09_engine_for_floor.c
void	floor_tex_casting(t_game *game, t_floor *floor, int x, int y);
void	ceil_tex_casting(t_game *game, t_floor *floor, int x, int y);
void	floor_casting(t_game *game, t_floor *floor, int x, int y);

// 09_engine_for_sprite.c
void	sprite_casting(t_game *game, t_sprite *item, int stripe);

// 09_engine_for_wall.c
void	texel_to_screen(t_game *game, t_raycast *raycast, int x);
void	dda(t_game *game, t_raycast *raycast);
void	wall_casting(t_game *game, int x);

// 09_setup_for_cast.c
void	set_sprite_ray(t_game *game, t_sprite *item);
void	set_floor_ray(t_game *game, t_floor *floor, int y);
void	set_wall_ray(t_game *game, t_raycast *raycast, int x);
void	set_side_dist(t_game *game, t_raycast *raycast);
void	set_for_draw(t_game *game, t_raycast *raycast);

// 09_run_ray_cast.c
void	draw(t_game *game);
void	calc(t_game *game);
int		main_loop(t_game *game);

// 10_clear_game.c
void	clear_screen_buf(t_game *game);
void	clear_map(t_list *map);
void	clear_path(t_path *path);
void	clear_map_buffer(char **map_buffer);
int		clear_cub(t_cub *cub);
void	clear_buf(t_game *game);
void	clear_tex(t_game *game);
void	clear_window(t_win *window);
void	clear_game(t_game *game);

// 12_make_bmp_file.c
int		save_bmp(t_game *game);

// print
void	print_path(t_path *path);
void	print_game(t_game *game);
void	print_node(t_list *list);
void	print_cub(t_cub *cub);
void	print_double_ptr(char **s);

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
char	**ft_strdup_double(char **s);
int		ft_strlcpy(char *dest, const char *src, int dstsize);

// gnl
int		get_next_line(int fd, char **line);

// split
char	**ft_split(char const *s, char c);
void	double_ptr_mem_free(char **str);

// lst
int		ft_lstsize(t_list *map);

#endif
