#include "pipex.h"

// /pipex file1 cmd1 cmd2 file2

static char	*cmd_path(char **env, char *cmd)
{
	int		i;
	char	**paths;

	i = 0;
	while (!ft_strnstr(env[i], "PATH=", 5))
		i++;
	env[i] = ft_substr(env[i], 6, ft_strlen(env[i]));
	paths = ft_split(env[i], ':');
	if (!env[i] || !(*paths)) // !paths || !(*paths) ?
 		return(merror(env[i], paths));
	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], cmd);
		if (!paths[i])
			return(merror(env[i], paths));
		if (!access(paths[i], F_OK) && !access(paths[i], X_OK))
			return(paths[i]);
		free(paths[i]);
	}
	return(0);
}

static void	ft_child2(int *end, char **av, char **env)
{
	int		f2;
	char	**tmp;

	tmp = ft_split(av[3], ' ');
	f2 = open(av[4], O_CREAT | O_WRONLY	| O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (f2 < 0)
		perror("Open f2");
	if (dup2(f2, 1) == -1)
		perror("Dup2 f2");
	if (dup2(end[0], 0) == -1)
		perror("Dup2 f2");
	close(f2);
	if (execve(cmd_path(env, tmp[0]), tmp, env) == -1)
		error("Execve f2");
	exit(EXIT_SUCCESS);
}

static void	ft_child1(int *end, char **av, char **env)
{
	int		f1;
	char	**tmp;

	tmp = ft_split(av[2], ' ');
	f1 = open(av[1], O_RDONLY);
	if (f1 < 0)
		error("Open f1");
	if (dup2(f1, 0) == -1)
		error("Dup2 f1");
	if (dup2(end[1], 1) == -1)
		error("Dup2 f1");
	close(f1);
	if (execve(cmd_path(env, tmp[0]), tmp, env) == -1)
		error("Execve f1");
	exit(EXIT_SUCCESS);
}

static char	*merror(char *s1, char **s2)
{
	int i;

	free(s1);
	i = 0;
	while (s2[i])
		free(s2[i++]);
	return (0);
}

static void	error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av, char **env)
{	
	int		end[2];
	//int		status;
	pid_t	child;

	if (ac != 5)
		return (write(2, "Wrong number of arguments\n", 27));
	if (pipe(end) == -1)
		error("Pipe");
	child[0] = fork();	
	if (child[0] == -1)
			error("Fork");
	if (child[0] == 0)
		ft_child1(end, av, env);
	waitpid(child[0], NULL, 0);
	ft_child2(end, av, env); //paretn
	close(end[0]);
	close(end[1]);
	return (0);
}