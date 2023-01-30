NAME = Cub3D

SRCS =  main.c

OBJS = $(SRCS:.c=.o)

CC = @cc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror


all : 	${NAME}

${NAME} : ${OBJS}
		@make -C libft/
		${CC} ${CFLAGS} libft/libft.a -L /Users/$(USER)/readline/lib -l readline ${OBJS} -o ${NAME}

clean :
	@make clean -C libft/
	@${RM} ${OBJS}

fclean : clean
	@make fclean -C libft/
	@${RM} ${NAME}

re : fclean all

.PHONY: all clean fclean re