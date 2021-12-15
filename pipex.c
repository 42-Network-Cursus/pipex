#include "pipex.h"

// /pipex file1 cmd1 cmd2 file2

int main(int ac, char **av, char **env)
{
	int		end[2]; // 1 == in, 0 == out
	int		f1;
	int		f2;
	
	//ft_check_args();
	f1 = open("file1");
	f2 = open("file2");
	if (f1 f2)
		//error
	pipe(end);
	//return values:
	//succes == 0
	if (parent == -1)
		//error_manager
	if (parent == 0)
		//child
	else
		//parent
	//error == -1 -> errno indicates error type | end var unchanged 

	pid_t	parent;
	
	parent = fork();
	//return values:
	//0 == child
	//non-0 == parent
	//-1 == error, no child + cfr errno
	#child
	dup2(f1, 0);
	if	(== -1)
		//error
	dup2(end[1], 1); //stdout of 1st cmd is entry of pipe
	if (== -1)
		//error
	close(end[0]);
	//execve

	#parent
	waitpid(...); //wait for child to finish
	dup2(f2, 1); //out
	if (== -1)
		//error
	dup2(end[0], 0) //in
	if (== -1)
		//error
	close(end[1]);
	close(f2);
	//execve
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