#ifndef PIPEX_H
# define PIPEX_H

#include "libft/libft.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

static void	ft_error(char *str);
static void	ft_child(int *end, char **av, char **env);
static void	ft_parent(int *end, char **av, char **env);
static char	*cmd_path(char **env, char *cmd);

#endif