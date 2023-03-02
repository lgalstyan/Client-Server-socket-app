#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
# include <readline/readline.h>
# include <readline/history.h>
#include "server_client.h"

# define ESC_GREEN          "\001\033[0;32m\002"
# define ESC_WHITE 		    "\001\033[0;37m\002"

int main(int argc, char **argv)
{
    if (argc != 3)
        return (2);
    char *ip = argv[1];
    int port = atoi(argv[2]);
    int sock;
    struct sockaddr_in addr;
    // socklen_t addr_size;
    char *line;
    line = NULL;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0){
        perror("[-]Socket error");
        exit(1);
    }
    // printf("[+]TCP server socket created.\n");
    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr.s_addr = inet_addr(ip);

    // printf("Connected to the server.\n");
    while (1)
    {
        connect(sock, (struct sockaddr*)&addr, sizeof(addr));
        bzero(line, 1024);
        printf(ESC_GREEN);
	    // line = readline("💚 client> "ESC_WHITE);
	    if (!line)
	    	continue ;
        printf("Client: %s\n", line);
        send(sock, line, strlen(line), 0);
        bzero(line, 1024);
        recv(sock, line, sizeof(line), 0);
        printf("Server: %s\n", line);
        if (!ft_strcmp(line, "disconnect"))
        {
            close(sock);
            printf("Disconnected from the server.\n");
            return (2);
        }
        free(line);
    }
    return (0);

}