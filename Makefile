SRCS			=	./00_check.c ./00_error.c ./00_run_cast.c ./00_set_game.c ./00_set_ray_cast.c \
					./01_read.c ./02_init.c ./03_parsing.c ./04_clear.c \
					./05_list_to_buffer.c ./05_map_valid.c ./06_texture.c ./07_key.c ./08_ray_cast.c\
					./utils/ft_atoi.c ./utils/ft_gnl.c ./utils/ft_lstsize.c \
					./utils/ft_utils_is.c ./utils/ft_utils_str.c ./main1.c \
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