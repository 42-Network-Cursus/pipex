#include "pipex.h"

// /pipex file1 cmd1 cmd2 file2

int	main(int argc, char **argv) 
{
	char *args[] = {"ls", "-aF", "/", 0};	/* each element represents a command line argument */
	char *env[] = { 0 };	/* leave the environment list null */

	printf("About to run /bin/ls\n");
	execve("/./bin/ls", args, env);
	perror("execve");	/* if we get here, execve failed */
	exit(1);
}