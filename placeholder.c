
static void	pipex(t_var data)
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