SRCS			=	./cub3d.c ./srcs/00_key_handle.c ./srcs/01_check_arg.c\
					./srcs/01_check_map_file_1.c ./srcs/01_check_map_file_2.c ./srcs/02_print_error.c\
					./srcs/03_init_for_parsing.c ./srcs/03_init_for_raycasting.c ./srcs/03_setup_for_game.c\
					./srcs/04_read_map_file.c ./srcs/05_parse_map_file.c ./srcs/06_list_to_buffer.c\
					./srcs/07_valid_map_buffer.c ./srcs/07_utils_for_validation.c ./srcs/08_load_texture_file.c\
					./srcs/09_engine_for_floor.c ./srcs/09_engine_for_sprite.c ./srcs/09_engine_for_wall.c\
					./srcs/09_run_ray_cast.c ./srcs/09_setup_for_cast.c ./srcs/10_clear_game.c ./srcs/11_utils_print.c\
					./srcs/12_make_bmp_file.c\
					./utils/ft_atoi.c ./utils/ft_gnl.c ./utils/ft_lstsize.c \
					./utils/ft_utils_is.c ./utils/ft_utils_str.c\
					./utils/ft_split.c
INCS			=	./includes#/cub3d.h ./includes/struct.h ./includes/constant.h
OBJS			= $(SRCS:.c=.o)
CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I$(INCS) #-g -fsanitize=address
LIBS 			= -L./mlx -lmlx -framework OpenGL -framework Appkit -lm
NAME			= cub3D
MLX				= libmlx.dylib

all:			$(NAME)

$(MLX):			
				make -C ./mlxbeta
				mv ./mlxbeta/$(MLX) .

$(NAME):		$(MLX) $(OBJS)
				make -C ./mlx
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) $(MLX)

clean:
				make clean -C ./mlx
				make clean -C ./mlxbeta
				$(RM) $(OBJS) $(MLX)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re fsan