SRCS			=	./00_check.c ./00_error.c ./01_read.c \
					./02_init.c ./03_parsing.c ./04_clear.c \
					./ft_atoi.c ./ft_gnl.c ./ft_lstsize.c \
					./ft_utils_is.c ./ft_utils_str.c ./main1.c \
					./ft_split.c ./05_list_to_buffer.c ./05_map_valid.c
OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -O3 -Wall -Wextra -Werror -I.

NAME			= cub3d

all:			$(NAME)

$(NAME):		$(OBJS)
				gcc ${CFLAGS} -o ${NAME} ${OBJS}


clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re