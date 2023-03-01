SERVER	= server
CLIENT	= client

SRCS 		= $(shell find "." -name "*.c")
OBJS		= $(SRCS:.c=.o)
GCC 		= gcc
CFLAGS		= -Wall -Werror -Wextra
RM		= rm -rf

all: $(SERVER) $(CLIENT)

$(SERVER) : ${OBJS}
	$(GCC) $(CFLAGS) server.o -o $(SERVER)

$(CLIENT) : $(OBJS)
	$(GCC) $(CFLAGS) client.o -o $(CLIENT)

clean :
	${RM} ${OBJS}

fclean: clean
	${RM} ${CLIENT} ${SERVER}

re : fclean all

.PHONY: all clean fclean re
