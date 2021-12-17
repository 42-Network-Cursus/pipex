//#include <stdio.h>
//#include <fcntl.h>
//#include <errno.h>

typedef struct s_struct
{
	char *cmd[2];
	int end[2];
}				t_struct;

int	main(int ac, char **av)
{
	acces("usr/bin");
/*
	printf("%s\n", a.cmd[0] = "zero");
	printf("%s\n", a.cmd[1] = "one");
	printf("%d\n", a.end[0] = 0);
	printf("%d\n", a.end[1] = 1);
	
	*/
	return (0);
}