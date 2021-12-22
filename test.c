#include "pipex.h"

int	main(int ac, char **av, char **env)
{	
	int		end[2];
	pid_t	child[2];

	if (pipe(end) == -1)
		error("Pipe");
	child[0] = fork();	
	if (child[0] == 0)
		printf("Child 0\n");
	else if (child[0] > 0)
	{
		child[1] = fork();
		if (child[0] == -1 || child[1] == -1)
			error("Fork");
		if (child[1] == 0)
			printf("Child 1\n");
	}
	waitpid(child[0], NULL, 0);
	waitpid(child[1], NULL, 0);
	close(end[0]);
	close(end[1]);
	return (0);
}