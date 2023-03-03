#include "server_client.h"

int main(int argc , char **argv)
{
	(void)argc;
	int sock;
    const char *ip = argv[1];
    int port = atoi(argv[2]);

	struct sockaddr_in server;
	char message[2000] , server_reply[2000];
	
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("Could not create socket");
	}
	// printf("Socket created\n");
	server.sin_addr.s_addr = inet_addr(ip);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	if (connect(sock, (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("connect failed. Error");
		return 1;
	}
	// printf("Connected\n");
	while(1)
	{
		printf(ESC_GREEN"Client> "ESC_WHITE);
		bzero(message, strlen(message));
		scanf("%s" , message);
		
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
		printf("serv_repl is %s\n", server_reply);
		if (!strncmp(server_reply, "disconnect", 10))
		{
			printf("eeey Client disconnected\n");
			// close(sock);
			fflush(stdout);
			break;
		}
		// printf("%s\n", server_reply);
	}
	close(sock);
	return 0;
}


// int main(){

//     char *ip = "127.0.0.1";
//     int port = 5566;
//     char *line; 
//     int sock;
//     int client_sock;
//     struct sockaddr_in addr;
//     char buffer[1024];  
//     line = NULL;
//     sock = socket(AF_INET, SOCK_STREAM, 0);
//     if (sock < 0){
//       perror("Socket error");
//       exit(1);
//     }
//     memset(&addr, '\0', sizeof(addr));
//     addr.sin_family = AF_INET;
//     addr.sin_port = port;
//     addr.sin_addr.s_addr = inet_addr(ip);   
//     connect(sock, (struct sockaddr*)&addr, sizeof(addr));
//     printf("Connected to the server.\n");   
//     bzero(buffer, 1024);
//     line = readline("Client> ");
//     strcpy(buffer, line);
//     printf("Client: %s\n", buffer);
//     client_sock = send(sock, buffer, strlen(buffer), 0);
//     if (client_sock < 0)
//     {
// 	    perror("accept failed");
// 	    return (3);
//     }
//     printf("Server: %s\n", buffer);

//     bzero(buffer, 1024);
//     recv(sock, buffer, sizeof(buffer), 0);

// //   close(sock);
// //   printf("Disconnected from the server.\n");
//     return 0;
// }



// int main(int argc, char **argv)
// {
//     if (argc != 3)
//         return (2);
//     char *ip = argv[1];
//     int port = atoi(argv[2]);
//     int sock;
//     struct sockaddr_in addr;
    
//     char *line;
//     line = NULL;
//     sock = socket(AF_INET, SOCK_STREAM, 0);
//     if (sock < 0)
//     {
//         perror("Socket error");
//         exit(1);
//     }
//     memset(&addr, '\0', sizeof(addr));
//     addr.sin_family = AF_INET;
//     addr.sin_port = port;
//     addr.sin_addr.s_addr = inet_addr(ip);

//     while (1)
//     {
//         connect(sock, (struct sockaddr*)&addr, sizeof(addr));
//         bzero(line, 1024);
// 	    line = readline("💚 client> "ESC_WHITE);
// 	    if (!line)
// 	    	continue ;
//         printf("Client: %s\n", line);
//         send(sock, line, strlen(line), 0);
//         bzero(line, 1024);
//         recv(sock, line, sizeof(line), 0);
//         printf("Server: %s\n", line);
//         if (!ft_strcmp(line, "disconnect"))
//         {
//             close(sock);
//             printf("Disconnected from the server.\n");
//             return (2);
//         }
//         free(line);
//     }
//     return (0);

// }