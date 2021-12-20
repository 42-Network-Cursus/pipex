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

static int	pipex(t_var *data);
static int	ft_child1(t_var *data, int *end);
static int	ft_child2(t_var *data, int *end);
static int exec_cmd(t_var data, char *path, int n);
static char *find_path(t_var *data, int n);

#endif