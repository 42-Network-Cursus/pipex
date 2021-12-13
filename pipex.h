#ifndef PIPEX_H
# define PIPEX_H

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