#include "server_client.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc , char **argv)
{
    (void)argc;
    (void)argv;
	int sock;
    const char *ip = argv[1];
    int port = atoi(argv[2]);
    printf("_%d_\n", port);
	struct sockaddr_in server;
	char message[1000] , server_reply[2000];
	
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");
	
	server.sin_addr.s_addr = inet_addr(ip);
	server.sin_family = AF_INET;
	server.sin_port = htons(8080);

	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("connect failed. Error");
		return 1;
	}
	
	puts("Connected\n");

	while(1)
	{
        printf(ESC_GREEN);
		printf("Client> ");
        printf(ESC_WHITE);
		scanf("%s" , message);
		
		if( send(sock , message , strlen(message) , 0) < 0)
		{
			puts("Send failed");
			return 1;
		}
		
		if( recv(sock , server_reply , 2000 , 0) < 0)
		{
			puts("recv failed");
			break;
		}
		
		puts("Server reply :");
		puts(server_reply);
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