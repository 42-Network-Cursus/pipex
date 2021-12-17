#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_data
{
	int		f1;
	int		f2;
	int		end[2]; // 1 == in, 0 == out
	char	*cmd[2];
	char	**env;
}				t_data;

// access, unlink, close, read
// write, pipe, dup, dup2, execve, fork
#include <unistd.h>
// open
#include <fcntl.h>
// malloc, free, exit
#include <stdlib.h>
// waitpid, wait, 
#include <sys/types.h>
//#include <sys/wait.h>
// perror
#include <stdio.h>
//#include <errno.h> Needed ?
// strerror
#include <string.h>

#endif