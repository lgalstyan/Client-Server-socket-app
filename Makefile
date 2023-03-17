SERVER	= server
CLIENT	= client

SRCS 		= $(wildcard ./*.c)
OBJS		= $(patsubst ./%.c, ./%.o, $(SRCS))
GCC 		= gcc
CFLAGS		= -Wall -Werror -Wextra
LINKER		= -L./readline_larisa/lib -lreadline
INCLUDE		= -I. -I ./readline_larisa/include
READFL 	 	= -lreadline
RD			= ${shell find ${HOME} -name readline_larisa 2>/dev/null}
RM			= rm -rf

all: $(SERVER) $(CLIENT)

%.o: %.c
	@$(GCC) $(CFLAGS) $(INCLUDE) -o $@ -c $<

$(SERVER) : ${OBJS}
	@$(GCC) $(CFLAGS) utils.o server.o -o $(SERVER)
	@echo "$(GRN)$(NAME) Server compiled$(DEF)"


$(CLIENT) : $(OBJS)
	@$(GCC) $(CFLAGS) ${READFL} utils.o client.o ${LINKER} -o $(CLIENT)
	@echo "$(GRN)$(NAME) Client compiled$(DEF)"

clean :
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${CLIENT} ${SERVER}
	@echo "$(BLU)$(NAME) Deleted$(DEF)"

install:
	cd readline-master && make clean && ./configure --prefix=${RD} && make && make install

re : fclean all

.PHONY: all clean fclean re install

GRN = \033[0;32m
BLU = \033[0;34m