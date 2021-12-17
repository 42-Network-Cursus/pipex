NAME=pipex

SRC =		pipex.c
OBJ =		${SRC:.c=.o}
CC =		gcc
CFLAGS =	-Wall -Wextra -Werror

all :		${NAME}

${NAME} :	${OBJ}
		${MAKE} -C ./libft
		${CC} ${CFLAGS} ${OBJ} ./libft/libft.a -o ${NAME}

clean : 
		${MAKE} -C ./libft fclean
		rm -rf ${OBJ}

fclean :	clean
		rm -rf ${NAME}

re :		fclean all

.PHONY:		all clean fclean re