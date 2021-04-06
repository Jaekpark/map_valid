#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

# define MAP_EXTENSION ".cub"
# define VALID_CHAR " 012NSEW"
# define SAVE "--save"

# define OPEN_MAX 32
# define NO_ARG 100
# define WRONG_NAME 101
# define WRONG_OPT 102
# define PARSING_ERR 103
# define OPEN_ERR 104

# define NORTH_TEX 10
# define SOUTH_TEX 11
# define EAST_TEX 12
# define WEST_TEX 13
# define SPRITE_TEX 14
# define FLOOR_TEX 15
# define CEIL_TEX 16
# define FLOOR_COL 17
# define CEIL_COL 18
# define RESOLUTION 19
# define EMPTY_LINE 20
# define MAP_LINE 21

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

typedef struct s_cub
{
	int		is_map;
	int		width;
	int		height;
	int		col;
	int		row;
	int		save_opt;
	int 	floor_color;
	int 	ceiling_color;
	t_list	*map;
	t_tex	*path;
}	t_cub;


t_list	*init_list(t_list *list)
{
	if (!(list = malloc(sizeof(t_list))))
		return (NULL);
	list->curr = NULL;
	list->head = NULL;
	list->tail = NULL;
	return (list);
}

t_tex	*init_tex(t_tex *path)
{
	if (!(path = malloc(sizeof(t_tex))))
		return (NULL);
	path->north = NULL;
	path->south = NULL;
	path->east = NULL;
	path->west = NULL;
	path->sprite = NULL;
	path->floor = NULL;
	path->ceil = NULL;
	return (path);
}

t_cub	*init_cub(t_cub *cub)
{
	if (!(cub = malloc(sizeof(t_cub))))
		return (NULL);
	cub->is_map = 0;
	cub->save_opt = 0;
	cub->width = 0;
	cub->height = 0;
	cub->floor_color = 0;
	cub->ceiling_color = 0;
	cub->col = 0;
	cub->row = 0;
	cub->map = init_list(cub->map);
	cub->path = init_tex(cub->path);
	return (cub);
}

int			ft_strlen(char *s)
{
	int		len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char		*ft_strdup(char *s1)
{
	char	*s1_tmp;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s1);
	if (!(s1_tmp = malloc(sizeof(char) * len + 1)))
		return (NULL);
	if (!s1)
		return (NULL);
	while (i < len)
	{
		s1_tmp[i] = s1[i];
		i++;
	}
	s1_tmp[i] = '\0';
	return (s1_tmp);
}

int				ft_atoi(const char *str)
{
	int			i;
	long long	sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		sign = (str[i] == '-') ? -1 : 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += (long long)(str[i] - '0');
		i++;
		if (result > 2147483648 && sign == -1)
			return (0);
		if (result > 2147483647 && sign == 1)
			return (-1);
	}
	return (result * sign);
}

char		*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*result;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1 || !s2)
		return (!s1 ? ft_strdup(s2) : ft_strdup(s1));
	if (!(result = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j])
		result[i++] = s2[j++];
	result[i] = '\0';
	free(s1);
	return (result);
}

char		*ft_strchr(char *s, int c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return (&s[i]);
	return (NULL);
}

int			ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1[i] == '\0' && s2[i] == '\0')
		return (-1);
	while (s1[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int			ft_strncmp(char *s1, char *s2, int num)
{
	int	i;

	i = 0;
	if (s1[i] == '\0' && s2[i] != '\0')
		return (-1);
	while (s1[i] && i < num)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int		ft_ismap(char *line)
{
	if (line[0] == 0)
		return (-1);
	while (*line)
	{
		if (!ft_strchr(VALID_CHAR, *line))
			return (-1);
		line++;
	}
	return (1);
}

int		ft_isnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (-1);
}

int		ft_isalpha(char c)
{
	if ((c >= 65 && c <= 90) || (c >=97 && c <= 122))
		return (1);
	return (-1);
}

int		ft_lstsize(t_list *map)
{
	t_node *temp;
	int	size;

	temp = map->head;
	size = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		size++;
	}
	return (size);
}

static int		word_count(char const *s, char c)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static int		*word_size(char const *s, char c)
{
	int		*arr;
	int		size;
	int		i;
	int		j;

	if (!(arr = malloc(sizeof(int) * word_count(s, c))))
		return (NULL);
	size = 0;
	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			size++;
			if (s[i + 1] == c || s[i + 1] == '\0')
			{
				arr[j] = size;
				size = 0;
				j++;
			}
		}
		i++;
	}
	return (arr);
}

static void		mem_allocate(char **dest, int *size, int count)
{
	int		i;

	i = 0;
	dest[count] = NULL;
	while (count)
	{
		dest[i] = malloc(sizeof(char) * size[i] + 1);
		i++;
		count--;
	}
}

void			split_mem_free(char **str)
{
	int		i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char			**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	int		*size;
	char	**dest;

	if (!s || !(dest = (char **)malloc(sizeof(char *) * word_count(s, c) + 1)))
		return (NULL);
	size = word_size(s, c);
	mem_allocate(dest, size, word_count(s, c));
	i = -1;
	j = 0;
	k = 0;
	while (s[++i])
		if (s[i] != c)
		{
			dest[j][k++] = s[i];
			if (s[i + 1] == c || s[i + 1] == '\0')
			{
				dest[j++][k] = '\0';
				k = 0;
			}
		}
	free(size);
	return (dest);
}


static int			get_line(char **temp, char **line, char *newline)
{
	char			*tmp;

	tmp = NULL;
	*newline = '\0';
	*line = ft_strdup(*temp);
	if (*(newline + 1) == '\0')
	{
		free(*temp);
		*temp = NULL;
	}
	else
	{
		tmp = ft_strdup(newline + 1);
		free(*temp);
		*temp = tmp;
	}
	return (1);
}

static int			check_temp(char **temp, char **line)
{
	char			*newline;

	newline = ft_strchr(*temp, '\n');
	if (*temp && newline != NULL)
		return (get_line(temp, line, newline));
	else if (newline == NULL && *temp)
	{
		*line = *temp;
		*temp = NULL;
	}
	else
		*line = ft_strdup("\0");
	return (0);
}

int					get_next_line(int fd, char **line)
{
	static char		*temp[OPEN_MAX];
	char			buf[2];
	char			*newline;
	int				byte_count;

	newline = NULL;
	if (fd < 0)
		return (-1);
	while ((byte_count = read(fd, buf, 1)) > 0)
	{
		buf[byte_count] = '\0';
		temp[fd] = ft_strjoin(temp[fd], buf);
		if ((newline = ft_strchr(temp[fd], '\n')) != NULL)
			break ;
	}
	if (byte_count < 0)
		return (-1);
	return (check_temp(&temp[fd], line));
}

void	clear_map(t_list *map)
{
	t_node	*temp;

	temp = NULL;
	while (map->head != NULL)
	{
		if (map->head->next == NULL)
		{
			free(map->head->line);
			free(map->head);
			break;
		}
		temp = map->head;
		while (temp->next->next != NULL)
			temp = temp->next;
		free(temp->next->line);
		free(temp->next);
		temp->next = NULL;
		if (temp != NULL)
			map->tail = temp;
	}
	free(map);
}

void	clear_path(t_tex *path)
{
	if (!path)
		return ;
	if (path->north != NULL)
		free(path->north);
	if (path->south != NULL)
		free(path->south);
	if (path->east != NULL)
		free(path->east);
	if (path->west != NULL)
		free(path->west);
	if (path->sprite != NULL)
		free(path->sprite);
	if (path->floor != NULL)
		free(path->floor);
	if (path->ceil != NULL)
		free(path->ceil);
	free(path);
}

void	clear_cub(t_cub *cub)
{
	if (!cub)
		return ;
	if (cub->path != NULL)
		clear_path(cub->path);
	cub->path = NULL;
	if (cub->map != NULL)
		clear_map(cub->map);
	cub->map = NULL;
	free(cub);
}

int parsing_path(t_cub *cub, char *line, int index)
{
	char **path;

	path = ft_split(line, ' ');
	if (!path)
		return (-1);
	else if (index == NORTH_TEX)
		cub->path->north = ft_strdup(path[1]);
	else if (index == SOUTH_TEX)
		cub->path->south = ft_strdup(path[1]);
	else if (index == EAST_TEX)
		cub->path->east = ft_strdup(path[1]);
	else if (index == WEST_TEX)
		cub->path->west = ft_strdup(path[1]);
	else if (index == SPRITE_TEX)
		cub->path->sprite = ft_strdup(path[1]);
	else if (index == FLOOR_TEX)
		cub->path->floor = ft_strdup(path[1]);
	else if (index == CEIL_TEX)
		cub->path->ceil = ft_strdup(path[1]);
	split_mem_free(path);
	return (1);
}

int	check_color(char *line)
{
	int i;
	int comma;
	int	flag;

	i = 0;
	comma = 0;
	flag = 0;
	printf("%s\n", line);
	while (line[++i] != '\0')
	{
		if (flag == 0 && ft_isnum(line[i]))
			flag = 1;
		if (flag == 1 && (line[i] == ' ' && ft_isnum(line[i + 1])))
			return (-1);
		if (line[i] == ',')
		{
			flag = 0;
			comma++;
			if (comma > 2)
				return (-1);
		}
	}
	return (1);
}

int parsing_color(t_cub *cub, char *line, int index)
{
	int r;
	int g;
	int b;
	int ret;
	char **color;

	if ((ret = check_color(line)) == -1)
		return (-1);
	color = ft_split(line, ',');
	r = ft_atoi(color[0]);
	g = ft_atoi(color[1]);
	b = ft_atoi(color[2]);
	printf("r = %d\n g = %d\n, b = %d\n", r, g, b);
	if (index == CEIL_COL)
		cub->ceiling_color = ((r & 0x0ff) << 16) | ((g & 0x0ff) << 8) | (b & 0x0ff);
	else if (index == FLOOR_COL)
		cub->floor_color = ((r & 0x0ff) << 16) | ((g & 0x0ff) << 8) | (b & 0x0ff);
	split_mem_free(color);
	return (1);
}

int parsing_resolution(t_cub *cub, char *line)
{
	int i;
	int width;
	int height;
	char **display_size;

	i = 0;
	display_size = ft_split(line, ' ');
	while (display_size[i])
		i++;
	if (i != 3)
		return (-1);
	cub->width = ft_atoi(display_size[1]);
	cub->height = ft_atoi(display_size[2]);
	split_mem_free(display_size);
	return (1);	
}

int parsing_map(t_cub *cub, char *line)
{
	t_list	*tmp;
	t_node	*node;

	tmp = cub->map;
	cub->is_map = 1;
	if (!(node = malloc(sizeof(t_node))))
		return (-1);
	node->line = ft_strdup(line);
	node->next = NULL;
	tmp->curr = node;
	if (tmp->curr != NULL && (tmp->head == NULL && tmp->tail == NULL))
	{
		tmp->head = tmp->curr;
		tmp->tail = tmp->curr;
	}
	else
	{
		tmp->tail->next = tmp->curr;
		tmp->tail = tmp->curr;
	}
	return (1);
}


int		print_error(int error)
{
	if (error == NO_ARG)
		printf("Error : Argument does not exists.\n");
	else if (error == WRONG_NAME)
		printf("Error : Wrong file name. Please check your file name.\n");
	else if (error == WRONG_OPT)
		printf("Error : Unacceptable option. Using '--save' option.\n");
	else if (error == PARSING_ERR)
		printf("Error : Parsing error. Please check your map file.\n");
	else if (error == OPEN_ERR)
		printf("Error : Can't open file. Please check your file name or directory.\n");
	return (-1);
}

int		check_file_name(const char *file_name)
{
	int pos;

	if (!file_name)
		return (-1);
	if (ft_strlen((char *)file_name) < 5)
		return (-1);
	pos = ft_strlen((char *)file_name) - 4;
	while (pos--)
		file_name++;
	return (ft_strcmp((char *)file_name, MAP_EXTENSION));
}

int		check_option(const char *option)
{
	if (!option)
		return (-1);
	return (ft_strcmp((char *)option, SAVE));
}

int		check_identifier(char *line)
{
	if (line[0] == 0)
		return (EMPTY_LINE);
	else if (ft_strncmp(line, "R ", 2) == 0)
		return (RESOLUTION);
	else if (ft_strncmp(line, "NO", 2) == 0)
		return (NORTH_TEX);
	else if (ft_strncmp(line, "SO", 2) == 0)
		return (SOUTH_TEX);
	else if (ft_strncmp(line, "EA", 2) == 0)
		return (EAST_TEX);
	else if (ft_strncmp(line, "WE", 2) == 0)
		return (WEST_TEX);
	else if (ft_strncmp(line, "S ", 2) == 0)
		return (SPRITE_TEX);
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (FLOOR_COL);
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (CEIL_COL);
	else if (ft_strncmp(line, "FT", 2) == 0)
		return (FLOOR_TEX);
	else if (ft_strncmp(line, "ST", 2) == 0)
		return (CEIL_TEX);
	else if (ft_ismap(line) == 1)
		return (MAP_LINE);
	else
		return (-1);
}

int		check_argv(int argc, char **argv, t_cub *cub)
{
	if (argc < 2)
		return (print_error(NO_ARG));
	else if (argc >= 2)
	{
		if (check_file_name(argv[1]) != 0)
			return (print_error(WRONG_NAME));
		else if (argc >= 3)
		{
			if (check_option(argv[2]) != 0)
				return (print_error(WRONG_OPT));
			else if (check_option(argv[2]) == 0)
				cub->save_opt = 1;
		}
	}
	return (1);
}


void print_node(t_list *list)
{
	t_node *temp;

	temp = list->head;
	while (temp != NULL)
	{
		printf("%s\n", temp->line);
		temp = temp->next;
	}
}

void	print_cub(t_cub *cub)
{
	printf("width = %d\n", cub->width);
	printf("height = %d\n", cub->height);
	printf("map size = %d\n", ft_lstsize(cub->map));
	printf("floor color = %d\n", cub->floor_color);
	printf("ceiling color = %d\n", cub->ceiling_color);
	printf("north : %s\n", cub->path->north);
	printf("south : %s\n", cub->path->south);
	printf("east : %s\n", cub->path->east);
	printf("west : %s\n", cub->path->west);
	printf("sprite : %s\n", cub->path->sprite);
	printf("floor tex : %s\n", cub->path->floor);
	printf("ceiling tex : %s\n", cub->path->ceil);
	printf("map\n");
	printf("head line [0] = %d\n", (int)cub->map->head->line[0]);
	print_node(cub->map);

}

int		parse_line(t_cub *cub, char *line)
{
	int ret;
	int index;

	ret = 0;
	if (!cub)
		return (-1);
	if (!(index = check_identifier(line)))
		return (-1);
	if (index >=NORTH_TEX && index <= CEIL_TEX)
		ret = parsing_path(cub, line, index);
	else if (index == FLOOR_COL || index == CEIL_COL)
		ret = parsing_color(cub, line, index);
	else if (index == RESOLUTION)
		ret = parsing_resolution(cub, line);
	else if (index == MAP_LINE)
		ret = parsing_map(cub, line);
	else if (index == EMPTY_LINE && cub->is_map == 1)
		ret = -1;
	else if (index == EMPTY_LINE && cub->is_map == 0)
		ret = 1;
	return (ret);
}

int		read_file(int argc, char **argv, t_cub *cub)
{
	int		fd;
	int 	eof;
	int 	ret;
	char	*line;

	ret = 0;
	eof = 1;
	line = NULL;
	if ((fd = open("./1.cub", O_RDONLY)) < 0)
		return (print_error(OPEN_ERR));
	while ((eof = get_next_line(fd, &line)) >= 0)
	{
		ret = parse_line(cub, line);
		free(line);
		if (eof <= 0 || ret < 0)
			break;
	}
	close(fd);
	return (ret);
}

int main(int argc, char **argv)
{
	int ret;
	t_cub *cub;

	cub = init_cub(cub);
	if ((ret = read_file(argc, argv, cub)) == -1)
	{
		clear_cub(cub);
		printf("ret = %d\n", ret);
	}
	else
	{
		print_cub(cub);
		clear_cub(cub);
	}

	system("leaks a.out > leaks_result_temp; cat leaks_result_temp | grep leaked && rm -rf leaks_result_temp");
	return (0);
}
