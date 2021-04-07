#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

# define MAP_EXTENSION ".cub"
# define VALID_CHAR " 012NSEW"
# define SAVE "--save"

# define OPEN_MAX 32
# define BUFFER_SIZE 128

# define NO_ARG 100
# define WRONG_NAME 101
# define WRONG_OPT 102
# define PARSING_ERR 103
# define OPEN_ERR 104
# define COLOR_ERR 105

# define NORTH_TEX 0
# define SOUTH_TEX 1
# define EAST_TEX 2
# define WEST_TEX 3
# define SPRITE_TEX 4
# define FLOOR_TEX 5
# define CEIL_TEX 6
# define FLOOR_COL 7
# define CEIL_COL 8
# define RESOLUTION 9
# define EMPTY_LINE 10
# define MAP_LINE 11

typedef struct s_pos
{
	double	pos_x;
	double 	pos_y;
}			t_pos;

typedef struct	s_img
{
	void	*img;
	int		*data;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
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

typedef struct s_tex
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*sprite;
	char	*floor;
	char	*ceil;
}	t_tex;

typedef struct	s_cub
{
	int is_map;
	int width;
	int height;
	int cols;
	int rows;
	int	save_opt;
	int floor_color;
	int ceiling_color;
	int	invalid_map;
	char **map_buffer;
	t_pos	player;
	t_list	*map;
	t_tex	*path;
}				t_cub;

typedef struct 	s_game
{

}	t_game;
// list_to_buffer
void	list_to_buffer(t_cub *cub);
char	*make_blank(int count);
int		set_base_width(char **map_buffer);
void	set_map_buffer(t_cub *cub);

// map_valid
void	map_dfs(t_cub *cub, char **visited, int x, int y);
int		find_player(t_cub *cub);
int		map_rows(char **map);
int		map_validation(t_cub *cub);
char	**ft_strdup_double(char **s);
void	print_double_ptr(char **s);

// read
void	print_node(t_list *list);
void	print_cub(t_cub *cub);
int		read_cub(char **argv, t_cub *cub);
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

// gnl
int		get_next_line(int fd, char **line);

// split
char	**ft_split(char const *s, char c);
void	split_mem_free(char **str);

// check
int		check_file_name(const char *file_name);
int		check_option(const char *option);
int		check_identifier(char *line);
int		check_argv(int argc, char **argv, t_cub *cub);

// error
int		print_error(int error);

// init
t_list	*init_list(t_list *list);
t_cub	*init_cub(t_cub *cub);
t_tex	*init_tex(t_tex *path);

// parsing
int		parsing_path(t_cub *cub, char *line, int index);
int		parsing_color(t_cub *cub, char *line, int index);
int		parsing_resolution(t_cub *cub, char *line);
int		parsing_map(t_cub *cub, char *line);

// clear
void	clear_map(t_list *map);
void	clear_path(t_tex *path);
void	clear_cub(t_cub *cub);
void	clear_map_buffer(char **map_buffer);


// lst
int		ft_lstsize(t_list *map);

#endif
