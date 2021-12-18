#include "pipex.h"

// /pipex file1 cmd1 cmd2 file2

static int end_path(char **str, t_data var)
{
	int i;

	i = 0;
	while (str[1])
	{
		str[i] = ft_strjoin(str[i], "/");
		if (!str[i])
			return(ft_error(5, var));
		i++;
	}
	return (0);
}

static int exec_cmd(t_data var, char *cmdn)
{
	char	**paths;
	char	**args;
	char	*cmd_path;
	int		i;

	i = 0;
	while (ft_strncmp(var.env[i], "PATH=", 5))
		i++;
	var.env[i] = ft_substr(var.env[i], 6, ft_strlen(var.env[i]));
	paths = ft_split(var.env[i], ':');
	if (end_path(paths, var))
		return (ft_error(5, var));
	args = ft_split(cmdn, ' ');
	i = -1;
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], args[0]);
		if (access(cmd_path, F_OK) && access(cmd_path, X_OK))
			return(ft_error(6, var));
		execve(cmd_path, args, var.env);
		//perror
		free(cmd_path);
	}
	return (0);
}

static int	ft_child(t_data var, int n)
{
	if (dup2(var.f2, 1) == -1) //out
		return(ft_error(4, var));
	if (dup2(var.end[0], 0) == -1) //in
		return(ft_error(4, var));
	close(var.end[1]);
	close(var.f2);
	exec_cmd(var, var.cmd[n]); //execve
	return (0);
}

static int	pipex(t_data var)
{
	int		status;
	pid_t	child1;
	pid_t	child2;
	
	if (pipe(var.end) == -1)
		return(ft_error(2, var));
	child1 = fork();
	if (child1 == -1)
		return(ft_error(3, var));
	if (child1 == 0)
		ft_child(var, 0);
	child2 = fork();
	if (child2 == -1)
		return(ft_error(3, var));
	if (child2 == 0)
		ft_child(var, 1);
	close(var.end[0]);
	close(var.end[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
	return (0);
}

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

int	main(int ac, char **av, char **env)
{
	t_data var;
	
	if (ac != 5)
		return (write(2, "Wrong number of arguments\n", 27));
	var.f1 = open(av[1], O_RDONLY);
	var.f2 = open(av[4], O_CREAT | O_WRONLY	| O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (var.f1 < 0 || var.f2 < 0)
		return(ft_error(1, var));
	var.cmd[0] = av[2];
	var.cmd[1] = av[3];
	var.env = env;
	pipex(var);
	return (0);
}