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
	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], cmd);
		if (!access(paths[i], F_OK) && !access(paths[i], X_OK))
			return(paths[i]);
		free(paths[i]);
	}
	return(0);
}

static void	ft_parent(int *end, char **av, char **env)
{
	int		f_out;
	char	**tmp;

	tmp = ft_split(av[3], ' ');
	f_out = open(av[4], O_CREAT | O_WRONLY	| O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (f_out < 0)
		perror("Open f_out");
	if (dup2(f_out, 1) == -1)
		perror("Dup2 f_out");
	if (dup2(end[0], 0) == -1)
		perror("Dup2 f_out");
	close(end[1]);
	if (execve(cmd_path(env, tmp[0]), tmp, env) == -1)
		error("Execve f_out");
}

static void	ft_child(int *end, char **av, char **env)
{
	int		f_in;
	char	**tmp;

	tmp = ft_split(av[2], ' ');
	f_in = open(av[1], O_RDONLY);
	if (f_in < 0)
		error("Open f_in");
	if (dup2(f_in, 0) == -1)
		error("Dup2 f_in");
	if (dup2(end[1], 1) == -1)
		error("Dup2 f_in");
	close(end[0]);
	if (execve(cmd_path(env, tmp[0]), tmp, env) == -1)
		error("Execve f_in");
}

static void	error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av, char **env)
{	
	int		end[2];
	pid_t	child;

	if (ac != 5)
		return (write(2, "Wrong number of arguments\n", 27));
	if (pipe(end) == -1)
		error("Pipe");
	child = fork();
	if (child == -1)
		error("Fork");	
	if (child[0] == 0)
		ft_child(end, av, env);
	else
		ft_parent(end, av, env);
	waitpid(child, NULL, 0);
	close(end[0]);
	close(end[1]);
	return (0);
}