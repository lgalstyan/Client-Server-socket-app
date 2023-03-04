#include "server_client.h"

int main(int argc , char **argv)
{
	(void)argc;
	int sock;
	if (argc != 3)
	{
		printf("IP and port arguments should be\n");
		return (1);
	}
    const char *ip = argv[1];
    int port = atoi(argv[2]);
	char *message = NULL;

	struct sockaddr_in server;
	// char message[2000] ;
	char server_reply[2000];
	
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("Could not create socket");
	}
	server.sin_addr.s_addr = inet_addr(ip);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	if (connect(sock, (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("connect failed. Error");
		return 1;
	}
	while(1)
	{
		// printf(ESC_GREEN"Client> "ESC_WHITE);
		// bzero(message, strlen(message));
		// message = readline(ESC_GREEN"Client> "ESC_WHITE);
		message = readline(">");
		// scanf("%s" , message);
		// puts("hello");
		// puts(message);
		
		if( send(sock , message , strlen(message) , 0) < 0)
		{
			printf("Send failed\n");
			return 1;
		}
		bzero(server_reply, strlen(server_reply));
		if( recv(sock , server_reply , 2000 , 0) < 0)
		{
			printf("recv failed\n");
			break;
		}
		// printf("serv_repl is %s\n", server_reply);
		if (!strncmp(server_reply, "disconnect", 10))
		{
			printf("Client disconnected\n");
			// fflush(stdout);
			// close(sock);
			break;
		}
		free(message);
		message = NULL;
	}
	// close(sock);
	return (0);
}