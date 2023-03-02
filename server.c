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
	int socket_desc , client_sock , c , read_size;
	struct sockaddr_in server , client;
	char client_message[2000];
	
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");
	
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8888 );
	
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("bind failed. Error");
		return 1;
	}
	puts("bind done");
	
	listen(socket_desc , 5);
	
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	
	client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
	if (client_sock < 0)
	{
		perror("accept failed");
		return 1;
	}
	puts("Connection accepted");
	
	while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
	{
		write(client_sock , client_message , strlen(client_message));
	    if(read_size == 0 || !ft_strcmp(client_message, "disconnect"))
	    {
	    	puts("Client disconnected");
	    	fflush(stdout);
	    }
		write(client_sock , ft_exec(client_message, env) , strlen(client_message));
        bzero(client_message, strlen(client_message));
	}
	
	if(read_size == -1)
	{
		perror("recv failed");
	}
	
	return 0;
}
