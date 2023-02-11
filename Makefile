NAME = Cub3D

SRCS =  main.c \
	gnl/get_next_line.c \
	gnl/get_next_line_utils.c \

CC = @cc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address

MLX =  -Imlx -lmlx -framework OpenGl -framework Appkit

all : 	${NAME}

${NAME} : ${SRCS}
		@make -C libft/
		${CC} ${CFLAGS} ${MLX} libft/libft.a ${SRCS} -o ${NAME}

clean :
	@make clean -C libft/
	@${RM} ${NAME}

fclean : clean
	@make fclean -C libft/
	@${RM} ${NAME}

re : fclean all

.PHONY: all clean fclean re