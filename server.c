#include "server_client.h"

char	*accses_to_exec(char *cmd, char *path)
{
	int		i;
	char	**token;
	char	*cmd_accs;
	char	*tmp;

	i = 0;
	tmp = NULL;
	token = ft_split(path, ':');
	if (cmd[0] != '.')
	{
		tmp = ft_strjoin("/", cmd);
		cmd = tmp;
	}
	while (token[i])
	{
		cmd_accs = ft_strjoin(token[i], cmd);
		if (access(cmd_accs, 0) == 0)
			return (cmd_accs);
		i++;
	}
	return (cmd);
}

static int	child_proc(char *cmd, char **env)
{
	char	*path;
	char	*cmd_acces;
	int		ret;

	path = "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki";
	cmd_acces = accses_to_exec(cmd, path);
	if (cmd[0] == '/' || cmd[0] == '.')
		ret = execve(cmd_acces, &cmd, env);
	else
		ret = execve(cmd_acces, &cmd, env);
	return (ret);
}

char *ft_exec(char *buff, char **env)
{
    int pid;

    pid = fork();
	if (pid == 0)
	{
		child_proc(buff, env);
    }
    return (buff);
}


int main(int argc , char **argv, char **env)
{
    (void)argc;
    (void)argv;
    (void)env;
	int flag = 0;
	int socket_desc;
	int client_desc;
	int c;
	int read_size;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char client_message[2000];
	
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Error: could not create socket\n");
	}
	printf("Socket created\n");
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(8080);
	
	if(bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("Error: bind failed!");
		return (1);
	}
	listen(socket_desc , 5);
	printf("Waiting for incoming connections...\n");
	c = sizeof(struct sockaddr_in);
	
	client_desc = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
	if (client_desc < 0)
	{
		perror("Error: accept failed");
		return (1);
	}
	printf("Connection accepted\n");
    bzero(client_message, strlen(client_message));
	// write(client_desc, client_message , strlen(client_message));
	while( (read_size = recv(client_desc , client_message , 2000 , 0)) > 0 )
	{
			printf("client message is:%s:\n", client_message);
		if (!strncmp(client_message, "disconnect", 10))
		{
			flag = 1;
			// send(client_desc, client_message, strlen(client_message), 0);
			write(client_desc, "Disconnection\n", 15);
			printf("Closed\n");
			close(client_desc);
			break;
		} else
			write(client_desc, client_message, strlen(client_message));
        bzero(client_message, strlen(client_message));
	}
	if(!flag && read_size == 0)
	{
		printf("Client disconnected\n");
		// fflush(stdout);
	}
	else if(!flag && read_size == -1)
	{
		perror("recv failed");
	}
	close(client_desc);
	return 0;
}
