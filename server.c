#include "server_client.h"

int main(int argc , char **argv, char **env)
{
    (void)argc;
    (void)argv;
    (void)env;
	int socket_desc;
	int client_desc;
	int c;
	int read_size;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char client_message[2000];
	// char **token;

	// token = NULL;
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Error: could not create socket\n");
	}
	printf("Socket created\n");
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(4242);
	if(bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("Error: bind failed!");
		return (1);
	}
	listen(socket_desc , 5);
	printf("Waiting for incoming connections...\n");
	c = sizeof(struct sockaddr_in);
	while (1)
	{
		client_desc = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
		if (client_desc < 0)
		{
			perror("Error: accept failed");
			return (1);
		}
		// printf("Connection accepted\n");
    	bzero(client_message, strlen(client_message));
		while ((read_size = recv(client_desc, client_message, 2000, 0)) > 0)
		{
			// printf("message %s\n", client_message);
			if (!strncmp(client_message, "shell", 5))
			{
				printf("message %s\n", client_message);
    			// bzero(client_message, strlen(client_message));
				// recv(client_desc, client_message, 2000, 0);
				printf("ft_clean%s\n", ft_clean_quots(client_message));
				puts("aaaaaaa");
			}
			write(client_desc, client_message, strlen(client_message));
    	    bzero(client_message, strlen(client_message));
		}
		if(read_size == 0)
		{
			printf("Client disconnected\n");
			// fflush(stdout);
		}
		else if(read_size == -1)
		{
			perror("recv failed");
		}
	}
	// close(client_desc);
	return 0;
}


			
			// token = ft_split(client_message, ' ');
			// if (!strncmp(token[0], "shell", 5) && token[1])
				// printf("token = %s\n", ft_clean_quots(token[1]));




		// {
		// 	flag = 1;
		// 	// send(client_desc, client_message, strlen(client_message), 0);
		// 	write(client_desc, "Disconnection\n", 15);
		// 	printf("Closed\n");
		// 	close(socket_desc);
		// 	// break;
		// } else