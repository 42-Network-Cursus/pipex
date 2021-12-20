#include "pipex.h"

// /pipex file1 cmd1 cmd2 file2

static char	*find_path(t_var *data, int n)
{
	int		i;
	char	**tmp;
	char	**paths;

	i = 0;
	while (!ft_strnstr(data.env[i], "PATH=", 5))
		i++;
	data.env[i] = ft_substr(data.env[i], 6, ft_strlen(data.env[i]));
	paths = ft_split(env[i], ':');
	tmp = ft_split(data.av[n], ' ');
	if (!env[i] || !paths || !tmp)
		//malloc error
	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], tmp[0]);
		if (paths[i])
			//malloc error
		if (access(paths[i], F_OK) && access(paths[i], X_OK))
			return(paths[i]);
		free(paths[i]);
	}
	exit(EXIT_FAILURE);
}

static void exec_cmd(t_var *data, char *path, int n)
{
	if (execve(path, data.av[n], data.env) == -1)
		perror("Execve");
	exit(EXIT_FAILURE);
}

static void	ft_child2(t_var *data, int *end)
{
	int		f2;
	char	*path;

	f2 = open(av[4], O_CREAT | O_WRONLY	| O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (f2 < 0)
		perror("Open");
	if (dup2(f2, 1) == -1)
		perror("Dup2");
	if (dup2(end[0], 0) == -1)
		perror("Dup2");
	close(end[0]);
	close(f2);
	path = find_path(data, 3);
	exec_cmd(data, path, 2);
}

static void	ft_child1(t_var *data, int *end)
{
	int		f1;
	char	*path;

	f1 = open(av[1], O_RDONLY);
	if (f1 < 0)
		perror("Open");
	if (dup2(f1, 0) == -1)
		perror("Dup2");
	if (dup2(end[1], 1) == -1)
		perror("Dup2");
	close(end[1]);
	close(f1);
	path = find_path(data, 2);
	exec_cmd(data, path, 2);
}

static void	pipex(t_var *data)
{
	int		end[2];
	int		status;
	pid_t	child1;
	pid_t	child2;
	
	if (pipe(end) == -1)
		perror("Pipe");
	child1 = fork();
	if (child1 == -1)
		perror("Fork");
	if (child1 == 0)
		ft_child1(data, end);
	child2 = fork();
	if (child2 == -1)
		perror("Fork");
	if (child2 == 0)
		ft_child2(data, end);
	close(end[0]);
	close(end[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
}

int	main(int ac, char **av, char **env)
{	
	t_var	*data;

	if (ac != 5)
		return (write(2, "Wrong number of arguments\n", 27));
	data.av = av;
	data.env = env;
	pipex(data);
	return (0);
}

/*
static int	ft_error(int n, t_data var)
{
	char *src;

	if (n == 1)
		src = "open";
	else if (n == 2)
		src = "pipe";
	else if (n == 3)
		src = "fork";
	else if (n == 4)
		src = "dup2";
	else if (n == 5)
		return (write(2, "Malloc failed\n", 15));
	else if (n == 6)
		src = "acces";
	perror(src);
	close(var.f1);
	close(var.f2);
	close(var.end[0]);
	close(var.end[1]);
	return (1);
}
*/