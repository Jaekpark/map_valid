SRCS			=	./cub3d.c ./srcs/key_handle.c ./srcs/check_arg.c \
					./srcs/check_map_file_1.c ./srcs/check_map_file_2.c ./srcs/print_error.c \
					./srcs/init_for_parsing.c ./srcs/init_for_raycasting.c ./srcs/setup_for_game.c \
					./srcs/read_map_file.c ./srcs/parse_map_file.c ./srcs/list_to_buffer.c \
					./srcs/valid_map_buffer.c ./srcs/utils_for_validation.c ./srcs/load_texture_file.c \
					./srcs/engine_for_floor.c ./srcs/engine_for_sprite.c ./srcs/engine_for_wall.c \
					./srcs/run_ray_cast.c ./srcs/setup_for_cast.c ./srcs/clear_game_1.c \
					./srcs/make_bmp_file.c ./srcs/clear_game_2.c ./srcs/key_update.c ./srcs/make_bmp.c \
					./utils/ft_atoi.c ./utils/ft_gnl.c ./utils/ft_lstsize.c \
					./utils/ft_utils_is.c ./utils/ft_utils_str_1.c ./utils/ft_utils_str_2.c\
					./utils/ft_split.c
INCS			=	./includes
OBJS			= $(SRCS:.c=.o)
CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I$(INCS)
LIBS 			= -L./mlx -lmlx -framework OpenGL -framework Appkit
NAME			= cub3D
MLX				= libmlx.dylib

all:			$(NAME)

$(MLX):			
				make -C ./mlxbeta
				mv ./mlxbeta/$(MLX) .

$(NAME):		$(MLX) $(OBJS)
				make -C ./mlx
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) $(MLX)

norm:			
				norminette $(SRCS) $(INCS)/*.h
clean:
				make clean -C ./mlx
				make clean -C ./mlxbeta
				$(RM) $(OBJS) $(MLX)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re fsan