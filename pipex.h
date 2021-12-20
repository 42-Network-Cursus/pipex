#ifndef PIPEX_H
# define PIPEX_H

typedef	struct	s_var
{
	char	**av;
	char	**env;
}				t_var;

#include "libft/libft.h"
// access, unlink, close, read
// write, pipe, dup, dup2, execve, fork
#include <unistd.h>
// open
#include <fcntl.h>
// malloc, free, exit
#include <stdlib.h>
// waitpid, wait, 
#include <sys/types.h>
#include <sys/wait.h>
// perror
#include <stdio.h>
#include <errno.h>
// strerror
#include <string.h>

static void	error(char *str);
static void	ft_child1(int *end, char **av, char **env);
static void	ft_child2(int *end, char **av, char **env);
static char	*cmd_path(char **env, char *cmd);

#endif