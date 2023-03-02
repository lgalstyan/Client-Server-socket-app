#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PORT               8080
# define ESC_GREEN          "\001\033[0;32m\002"
# define ESC_WHITE 		    "\001\033[0;37m\002"

int	ft_strcmp(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
#endif