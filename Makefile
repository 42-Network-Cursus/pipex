# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwastche <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/23 13:14:46 by cwastche          #+#    #+#              #
#    Updated: 2021/12/23 13:14:48 by cwastche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
