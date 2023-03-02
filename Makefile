SERVER	= server
CLIENT	= client

SRCS 		= utils.c
OBJS		= $(SRCS:.c=.o)
GCC 		= gcc
CFLAGS		= -Wall -Werror -Wextra
RM			= rm -rf

# %.o : %.c
# 	${GCC} ${CFLAGS} -I server_client.h -c $< -o ${<:.c=.o}

all: $(SERVER) $(CLIENT)

$(SERVER) : ${OBJS} server.o
	$(GCC) $(CFLAGS) $(SRCS) server.o -o $(SERVER)

$(CLIENT) : $(OBJS) client.o
	$(GCC) $(CFLAGS) $(SRCS) client.o -o $(CLIENT)

clean :
	${RM} ${OBJS} server.o client.o

fclean: clean
	${RM} ${CLIENT} ${SERVER}

re : fclean all

.PHONY: all clean fclean re
