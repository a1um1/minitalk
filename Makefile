CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./includes

SERVER_SRCS		=	./server.c
SERVER_OBJ		=	${SERVER_SRCS:.c=.o}
SERVER_NAME		=	server

CLIENT_SRCS		=	./client.c
CLIENT_OBJ		=	${CLIENT_SRCS:.c=.o}
CLIENT_NAME		=	client


B_SERVER_SRCS	=	./server_bonus.c
B_SERVER_OBJ	=	${SERVER_SRCS:.c=.o}
B_SERVER_NAME	=	server_bonus

B_CLIENT_SRCS	=	./client_bonus.c
B_CLIENT_OBJ	=	${CLIENT_SRCS:.c=.o}
B_CLIENT_NAME	=	client_bonus


all: ft_printf/libftprintf.a ${SERVER_NAME} ${CLIENT_NAME}

bonus: ft_printf/libftprintf.a ${B_SERVER_NAME} ${B_CLIENT_NAME}

.c.o: 		includes/minitalk_server.h includes/minitalk_client.h
	${CC} ${CFLAGS} -c $< -o $@

ft_printf/libftprintf.a:
	make -C ft_printf

${SERVER_NAME}: ${SERVER_OBJ}
	${CC} ${CFLAGS} ${SERVER_OBJ} ft_printf/libftprintf.a -o ${SERVER_NAME}

${CLIENT_NAME}: ${CLIENT_OBJ}
	${CC} ${CFLAGS} ${CLIENT_OBJ} ft_printf/libftprintf.a -o ${CLIENT_NAME}

${B_SERVER_NAME}: ${B_SERVER_OBJ}
	${CC} ${CFLAGS} ${B_SERVER_OBJ} ft_printf/libftprintf.a -o ${B_SERVER_NAME}

${B_CLIENT_NAME}: ${B_CLIENT_OBJ}
	${CC} ${CFLAGS} ${B_CLIENT_OBJ} ft_printf/libftprintf.a -o ${B_CLIENT_NAME}

clean:
	make -C ft_printf clean
	rm -f ${SERVER_OBJ} ${CLIENT_OBJ} ${B_CLIENT_OBJ} ${B_SERVER_OBJ}

fclean:		clean
	make -C ft_printf fclean
	rm -f ${SERVER_NAME} ${CLIENT_NAME} ${B_SERVER_NAME} ${B_CLIENT_NAME}

re:			fclean all

norm:
	norminette $(SERVER_SRCS) $(CLIENT_SRCS) $(B_SERVER_SRCS) $(B_CLIENT_SRCS) | grep -v Norme -B1 || true

.PHONY: all clean fclean re debug norm bonus
