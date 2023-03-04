#include "server_client.h"

char *ft_clean_quots(char *str)
{
	unsigned int	i;
	char *res;

	i = 1;
	// while (str && str[i] && str[i] != '\"')
	// 	i++;
	printf("in ft_clean str  %s\n", str);
	res = malloc(sizeof(char) * (strlen(str) - i - 1));
	while(str && str[i] && ((i + 1) < strlen(str)) && str[i] != '\"')
	{
		puts(&str[i]);
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	// free(str);
	printf("in ft_clean res  %s\n", res);
	return (res);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc (strlen (s1) + strlen (s2) + 1);
	if (!str)
		return (0);
	if (!s1)
		return (s2);
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
		{
			return ((int)((unsigned char)s1[i] - (unsigned char)s2[i]));
		}
		if (s1[i] == '\0')
			return ((-1) * s2[i]);
		i++;
	}
	return (0);
}

static size_t	cnt_word(char const *str, char delim)
{
	size_t	prev_del;
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	prev_del = 1;
	while (str[i])
	{
		if (str[i] == delim)
			prev_del = 1;
		else if (prev_del)
			count++;
		if (str[i] != delim)
			prev_del = 0;
		i++;
	}
	return (count);
}

static char	*tokenize(char const *s, size_t st, size_t len)
{
	char	*tab;
	size_t	i;

	i = 0;
	tab = malloc(len + 1);
	if (!tab)
		return (NULL);
	while (s[st] && i < len)
	{
		tab[i] = s[st];
		st++;
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

static void	*free_tab(char **s, size_t i)
{
	while (i > 0)
	{
		free(s[i]);
		i--;
	}
	free(s);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**tab;
	size_t	start;
	size_t	end;

	start = 0;
	end = 0;
	i = -1;
	tab = malloc(sizeof(char *) * (cnt_word (s, c) + 1));
	if (!(tab) || !s)
		return (0);
	while (++i < cnt_word (s, c))
	{
		while (s[start] && s[start] == c)
			start++;
		end = start;
		while (s[end] && s[end] != c)
			end++;
		tab[i] = tokenize(s, start, end - start);
		if (!tab[i])
			free_tab (tab, i);
		start = end;
	}
	tab[i] = 0;
	return (tab);
}


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
