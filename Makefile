NAME = Cub3D

SRCS =  main.c \
	parsing/parsing.c \
	parsing/parsing2.c \
	parsing/parsing3.c \
	parsing/parsing4.c \
	parsing/parsing5.c \
	parsing/p_parsing.c \
	parsing/init_parsing.c \
	gnl/get_next_line.c \
	gnl/get_next_line_utils.c \
	raycasting/raycasting.c\
	raycasting/raycasting2.c\
	raycasting/raycasting_utils.c\
	raycasting/player.c \
	raycasting/castrays.c \
	raycasting/castrays2.c \
	raycasting/player_utils.c \
	#minilibx_opengl_20191021/libmlx.a\



CC = cc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address 

MLX = -Imlx -lmlx -framework OpenGl -framework Appkit

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