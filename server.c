#include "server_client.h"

static void	child_proc(int client, char **env);

int main(int argc , char **argv, char **env)
{
    (void)argc;
    (void)argv;
	int socket_desc;
	int client_desc;
	struct sockaddr_in server;
	struct sockaddr_in client;
	int c;
	int childpid;

	c = sizeof(struct sockaddr_in);
	socket_desc = socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
	if (socket_desc == -1)
	{
		perror("Error: could not create socket");
	}
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);
	int optival = 1;
	if (setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, &optival, sizeof(optival)) < 0)
	{
		perror("setsocket");
		exit(1);
	}
	if(bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("Error: bind failed!");
		return (1);
	}
	listen(socket_desc , 5);
	write(1, "Waiting for connections...\n", 28);
	while (1)
	{
		client_desc = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
		if (client_desc < 0)
		{
			perror("Error: accept failed");
			return (1);
		}
		write (1, ESC_GREEN"Client has successfully connected.\n"ESC_WHITE, 54);
		childpid = fork();
		if (childpid == 0)
		{
			child_proc(client_desc, env);
		}
	}
	return 0;
}

static void	child_proc(int client_desc, char **env)
{
	int read_size;
	char **token;
	char client_message[2000];
	int	output = dup(1);
	
	token = NULL;
	while ((read_size = recv(client_desc, client_message, 2000, 0)) > 0)
	{
		token = ft_split_2_part(client_message, ' ');
		if (token[0] && token[1] && !strncmp(token[0], "shell", 5) && token[1][0] == '\"')
		{
			char **a = ft_split(ft_clean_quotes(token[1]), ' ');
			dup2(client_desc, 1);
			ft_exec(a, env);
			dup2(1, client_desc);
		}
		else
			write(client_desc, client_message, strlen(client_message));
		free(token);
        bzero(client_message, strlen(client_message));
	}
	if(read_size == 0)
	{
		write(output, "Client disconnected\n", 21);
		return ;
	}
	else if(read_size == -1)
	{
		perror("recv failed");
		return ;
	}
}