#include "pipex.h"

// /pipex file1 cmd1 cmd2 file2

/*
	if (!end_path(paths, var))
		return (ft_error(5, var));
		while (str[1])
	{
		str[i] = ft_strjoin(str[i], "/");
		if (!str[i])
			return(ft_error(5, var));
		i++;
	}
*/

static char *find_path(char **av, char **env)
{
	int		i;
	char	*paths;
	char	*cmd;

	i = 0;
	while (!ft_strncmp(env[i], "PATH=", 5))
		i++;
	env[i] = ft_substr(env[i], 6, ft_strlen(env[i]));
	paths = ft_split(env[i], ':');
	printf("%s\n"paths[0]);
	printf("%s\n"paths[1]);
	printf("%s\n"paths[2]);
	printf("%s\n"paths[3]]);
	printf("%s\n"paths[4]);
	printf("%s\n"paths[5]);
	printf("%s\n"paths[6]);
	printf("%s\n"paths[7]);
	cmd = ft_split(cmdn, ' ');
	if (!env[i] || !paths || !cmd)
		//malloc error
	i = -1;
	while (paths[++i])
	{
		cmd = ft_strjoin(paths[i], cmd[0]);
		if (!cmd)
			//malloc error
		if (access(cmd, F_OK) && access(cmd, X_OK))
			break ;
		free(cmd);
	}
	return (cmd);
}

static void exec_cmd(char *cmd, char *cmd_path, char **env)
{
	if (execve(cmd_path, cmd, env == -1)
		perror("Execve");
	exit(EXIT_FAILURE);
}

static void	ft_child2(int *end, char **av, char *cmd_path, char **env)
{
	int f2;

	f2 = open(av[4], O_CREAT | O_WRONLY	| O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (f2 < 0)
		perror("Open");
	if (dup2(f2, 1) == -1)
		perror("Dup2");
	if (dup2(end[0], 0) == -1)
		perror("Dup2");
	close(end[0]);
	close(f2);
	exec_cmd(av[3], cmd_path, env);
}

static void	ft_child1(int *end, char **av, char *cmd_path, char **env)
{
	int f1;

	f1 = open(av[1], O_RDONLY);
	if (f1 < 0)
		perror("Open");
	if (dup2(f1, 0) == -1)
		perror("Dup2");
	if (dup2(end[1], 1) == -1)
		perror("Dup2");
	close(end[1]);
	close(f1);
	exec_cmd(av[2], cmd_path, env);
}

static void	pipex(char **av, char **env, char *cmd_path)
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
		ft_child1(end, av, cmd_path, env);
	child2 = fork();
	if (child2 == -1)
		perror("Fork");
	if (child2 == 0)
		ft_child2(end, av, cmd_path, env);
	close(end[0]);
	close(end[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
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
int	main(int ac, char **av, char **env)
{	
	char	*cmd_path;

	if (ac != 5)
		return (write(2, "Wrong number of arguments\n", 27));
	cmd_path = find_path(av, env);
	if (!cmd_path)
		//malloc error
	pipex(av, env, cmd_path);
	return (0);
}