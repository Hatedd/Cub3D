NAME = Cub3D

SRCS =  main.c \
	parsing.c \
	parsing2.c \
	map_utils.c \
	init_data.c \
	parsing_map.c \
	gnl/get_next_line.c \
	gnl/get_next_line_utils.c \
	minilibx_opengl_20191021/libmlx.a\

CC = @cc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

MLX =  -framework OpenGl -framework Appkit

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