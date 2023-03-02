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

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    char *ip = "127.0.0.1";
    char **token;

    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char *buffer;
    int n;

    buffer = NULL;
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0)
    {
        perror("Socket error\n");
        exit(1);
    }
    printf("TCP server socket created.\n");
    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = PORT;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (n < 0){
        perror("Bind error\n");
        exit(1);
    }
    printf("Bind to the port number: %d\n", PORT);
    listen(server_sock, 5);
    printf("Listening...\n");
    while(1)
    {
        addr_size = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
        printf("Client connected.\n");
        bzero(buffer, 1024);
        recv(client_sock, buffer, sizeof(buffer), 0);
        token = ft_split(buffer, ' ');
        printf("recv\n");
        bzero(buffer, 1024);
        if (token != NULL && token[0] != NULL && !ft_strcmp(buffer, "disconnect"))
        {
            send(client_sock, "disconnect", 10, 0);
            close(client_sock);
            printf("Client disconnected.\n\n");
        }
        else if (token != NULL && token[0] != NULL && !ft_strcmp(buffer, "shell"))
        {
            buffer = ft_exec(strtok(token[1], "\""), env);
            // strcpy(buffer, strlen(buffer));
            // strcpy(buffer, ft_exec(strtok(tokne[1], "\""), env));
            send(client_sock, buffer, strlen(buffer), 0);
        }
        else
            send(client_sock, buffer, strlen(buffer), 0);
    }

    return 0;
}