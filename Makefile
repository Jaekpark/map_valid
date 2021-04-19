SRCS			=	./00_cub3d.c ./00_key_handle.c ./01_check_arg.c\
					./01_check_map_file_1.c ./01_check_map_file_2.c ./02_print_error.c\
					./03_init_for_parsing.c ./03_init_for_raycasting.c ./03_setup_for_game.c\
					./04_read_map_file.c ./05_parse_map_file.c ./06_list_to_buffer.c\
					./07_valid_map_buffer.c ./07_utils_for_validation.c ./08_load_texture_file.c\
					./09_engine_for_floor.c ./09_engine_for_sprite.c ./09_engine_for_wall.c\
					./09_run_ray_cast.c ./09_setup_for_cast.c ./10_clear_game.c ./11_utils_print.c\
					./12_make_bmp_file.c\
					./utils/ft_atoi.c ./utils/ft_gnl.c ./utils/ft_lstsize.c \
					./utils/ft_utils_is.c ./utils/ft_utils_str.c\
					./utils/ft_split.c 
OBJS			= $(SRCS:.c=.o)
CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I. -g -fsanitize=address
LIBS 			= -L./mlx -lmlx -framework OpenGL -framework Appkit -lm
NAME			= cub3D
MLX				= libmlx.dylib

all:			$(NAME)
$(MLX):			
				make -C ./mlxbeta
				mv ./mlxbeta/$(MLX) .

$(NAME):		$(MLX) $(OBJS)
				make -C ./mlx
				gcc $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) $(MLX)


clean:
				make clean -C ./mlx
				make clean -C ./mlxbeta
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re