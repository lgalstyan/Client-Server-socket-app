#include "server_client.h"

int	create_connect(const char *ip, const int port)
{
	int sock;
	struct sockaddr_in server;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		perror("Could not create socket");
		return(-3);
	}
	server.sin_addr.s_addr = inet_addr(ip);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	if (connect(sock, (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("connect failed. Error");
		return (-3);
	}
	return (sock);
}

// char *pares(char *str)
// {
// 	if (!strncmp(str, "shell", 5))
// 		return (str + 5);
// 	else if (!strncmp(str, "help", 4))
// 		return (strdup("usage: shell \"command\""));
// 	else
// 		return (strdup("command not found"));
// 	return (str);
// }

int main(int argc , char **argv)
{
	(void)argc;
	if (argc != 3)
	{
		write(1, "IP and port arguments should be\n", 33);
		return (1);
	}
	int sock;
    const char *ip = argv[1];
    const int port = atoi(argv[2]);
	char *message = NULL;
	char server_reply[2000];

	sock = create_connect(ip, port);
	if (sock < 0)
		return (1);
	while(1)
	{
		message = readline(ESC_GREEN "Client> " ESC_WHITE);
		if (message[0])
			add_history(message);
		else
		{
			free(message);
			continue ;
		}
		if (!strncmp(message, "shell", 5))
		{
			if( send(sock, message + 6, strlen(message), 0) < 0)
			{
				perror("Send failed");
				return (1);
			}
		}
		else if (!strncmp(message, "help", 4))
		{
			write(1, "usage: shell \"command\"\n", 24);
			continue ;
		}
		else if (!strncmp(message, "disconnect", 10))
		{
			write(1, "Disconnected\n", 14);
			break;
		}
		else
		{
			write(1, "command not found\n", 19);
			continue ;
		}
		// else if (!strncmp(server_reply, "disconnect", 10))

		// message = pares(message);
		bzero(server_reply, strlen(server_reply));
		if( recv(sock , server_reply , 2000 , 0) < 0)
		{
			perror("recv failed");
			break;
		}
		// if (!strncmp(server_reply, "disconnect", 10))
		// {
		// 	write(1, "Disconnected\n", 14);
		// 	break;
		// }
		write(1, server_reply, strlen(server_reply));
		// write(1, "\n", 1);
		free(message);
		message = NULL;
	}
	close(sock);
	return (0);
}