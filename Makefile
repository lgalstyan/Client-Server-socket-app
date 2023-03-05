SERVER	= server
CLIENT	= client

SRCS 		= $(wildcard ./*.c)
OBJS		= $(patsubst ./%.c, ./%.o, $(SRCS))
GCC 		= gcc
CFLAGS		= -Wall -Werror -Wextra
RM			= rm -rf

all: $(SERVER) $(CLIENT)

%.o: %.c
	@$(GCC) $(CFLAGS) -I. -o $@ -c $<

$(SERVER) : ${OBJS}
	@$(GCC) $(CFLAGS) utils.o server.o -o $(SERVER)
	@echo "$(GRN)$(NAME) Server compiled$(DEF)"


$(CLIENT) : $(OBJS)
	@$(GCC) $(CFLAGS) utils.o client.o -lreadline -o $(CLIENT)
	@echo "$(GRN)$(NAME) Client compiled$(DEF)"

clean :
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${CLIENT} ${SERVER}
	@echo "$(BLU)$(NAME) Deleted$(DEF)"

re : fclean all

.PHONY: all clean fclean re

GRN = \033[0;32m
BLU = \033[0;34m