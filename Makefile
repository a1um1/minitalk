PROJECT_NAME	=	MiniTalk
AUTHOR			=	tlakchai

SERVER_SRC		=	server.c
SERVER_SRC_DIR	=	./
SERVER_SRCS	=	${addprefix ${SERVER_SRC_DIR}, ${SERVER_SRC}}
SERVER_OBJ		=	${SERVER_SRCS:.c=.o}
SERVER_NAME	=	"server"

CLIENT_SRC		=	client.c
CLIENT_SRC_DIR	=	./
CLIENT_SRCS	=	${addprefix ${CLIENT_SRC_DIR}, ${CLIENT_SRC}}
CLIENT_OBJ		=	${CLIENT_SRCS:.c=.o}
CLIENT_NAME	=	"client"

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./includes

all: ft_printf/libftprintf.a ${SERVER_NAME} ${CLIENT_NAME}

.c.o: 		includes/minitalk_server.h includes/minitalk_client.h
	${CC} ${CFLAGS} -c $< -o $@

ft_printf/libftprintf.a:
	make -C ft_printf

${SERVER_NAME}: ${SERVER_OBJ}
	${CC} ${CFLAGS} ${SERVER_OBJ} ft_printf/libftprintf.a -o ${SERVER_NAME}

${CLIENT_NAME}: ${CLIENT_OBJ}
	${CC} ${CFLAGS} ${CLIENT_OBJ} ft_printf/libftprintf.a -o ${CLIENT_NAME}

clean:
	make -C ft_printf clean
	rm -f ${SERVER_OBJ} ${CLIENT_OBJ}

fclean:		clean
	make -C ft_printf fclean
	rm -f ${SERVER_NAME} ${CLIENT_NAME}

re:			fclean all

norm:
	norminette $(SRC) . ./ft_printf | grep -v Norme -B1 || true

.PHONY: all clean fclean re debug norm
