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
OBJS			=	$(SRCS:.c=.o)
CC				=	gcc
RM				=	rm -rf
CFLAGS			=	-Wall -Wextra -Werror -I$(INCS)
LIBS 			=	-L./mlx -lmlx -framework OpenGL -framework Appkit
NAME			=	cub3D
BMP				=	./screenshot.bmp
MLX				=	libmlx.dylib

all:			$(NAME)

$(MLX):			
				make -C ./mlxbeta
				mv ./mlxbeta/$(MLX) .

$(NAME):		$(MLX) $(OBJS)
				make -C ./mlx
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) $(MLX)	

run:			$(NAME)
				./cub3D ./maps/valid_map.cub

leak:
				osascript -e 'tell app "Terminal" to do script "cd ~/jaekpark_42cursus/map_valid && ./cub3D ./maps/valid_map.cub"'
				osascript -e 'tell app "Terminal" to do script "while ; do leaks cub3D ; sleep 2 ; clear ; done"'

map_test:		clean $(NAME)
				git clone https://github.com/humblEgo/cub3D_map_tester.git map_tester
				./map_tester/test_map_valid_function.sh -f

bmp:			$(NAME)
				./cub3D ./maps/valid_map.cub --save
				open ./screenshot.bmp

norm:			
				norminette $(SRCS) $(INCS)/*.h

clean:
				make clean -C ./mlx
				make clean -C ./mlxbeta
				$(RM) $(OBJS) $(BMP) ./map_tester/

fclean:			clean
				$(RM) $(NAME) $(MLX)

re:				fclean $(NAME)

.PHONY:			all clean fclean re norm run bmp leak map_test