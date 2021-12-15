#include "pipex.h"

// /pipex file1 cmd1 cmd2 file2

static int end_path(char **str)
{
	while (*str)
	{
		*str = ft_join(*str, "/");
		if (*str)
			//error
		*str++
	}
}

static void exec_cmd(t_data var, char *cmdn)
{
	char **paths;
	char **args;
	char *cmd;

	while (ft_strncmp(*(var->env), "PATH="))
		*(var->env)++;
	*(var->env) = ft_substr(*(var->env), 6, ft_strlen(*(var->env)));
	path = ft_split(*(var->env), ":");
	if (end_path(path))
		//error
	args = ft_split(cmdn, " ");

	i = -1;
	while (paths[++i])
	{
		cmd = ft_join(paths[i]), args[0]);
		execve(cmd, args, var.env);
		//perror
		free(cmd);
	}

}

static void	ft_child2(t_data var, int *end)
{
	int status;

	dup2(var.f2, 1); //out
	if (== -1)
		//error
	dup2(end[0], 0) //in
	if (== -1)
		//error
	close(end[1]);
	close(var.f2);
	exec_cmd(var, var.cmd1); //execve
}

static void	ft_child1(t_data var, int *end)
{
	dup2(var.f1, 0);
	if	(== -1)
		//error
	dup2(end[1], 1); //stdout of 1st cmd is entry of pipe
	if (== -1)
		//error
	close(end[0]);
	close(var.f1);
	exec_cmd(var, var.cmd2) //execve
}

static void	pipex(t_data var)
{
	int		end[2]; // 1 == in, 0 == out
	pid_t	child1;
	pid_t	child2;
	
	if (!pipe(end))
		//pipe error
	child1 = fork();
	if (child1 == -1)
		//error_manager
	if (child == 0)
		ft_child1(var, end);
	child2 = fork();
	if (child2 == -1)
		//error
	if (child2 == 0)
		ft_child2(var, end);
	close(end[0]);
	close(end[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
}

int	main(int ac, char **av, char **env)
{
	t_data var;
	
	//ft_check_args();
	var.f1 = open("file1");
	var.f2 = open("file2");
	if (var.f1 < 0 || var.f2 < 0)
		return(-1); //errno ?
	var.cmd1 = av[2];
	var.cmd2 = av[4];
	var.env = env;
	pipex(var);
	return (0);
}


// WORKS IN MAC/LINUX TERMINAL
/*
int	main(int argc, char **argv) 
{
	char *args[] = {"ls", "-aF", "/", 0};	// each element represents a command line argument
	char *env[] = { 0 };	// leave the environment list null

	printf("About to run /bin/ls\n");
	execve("/./bin/ls", args, env);
	perror("execve");	// if we get here, execve failed 
	exit(1);
}*/