SRCS			=	./00_check.c ./00_error.c ./01_read.c \
					./02_init.c ./03_parsing.c ./04_clear.c \
					./utils/ft_atoi.c ./utils/ft_gnl.c ./utils/ft_lstsize.c \
					./utils/ft_utils_is.c ./utils/ft_utils_str.c ./main1.c \
					./utils/ft_split.c ./05_list_to_buffer.c ./05_map_valid.c
OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -O3 -Wall -Wextra -Werror -I.
LIBS 			= -L./mlx -lmlx -framework OpenGL -framework Appkit -lm
NAME			= cub3D

all:			$(NAME)

$(NAME):		$(MLX) $(OBJS)
				make -C ./mlx
				gcc $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)


clean:
				make clean -C ./mlx
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re