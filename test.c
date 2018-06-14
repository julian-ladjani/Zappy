
#include "stdio.h"
#include <unistd.h>

int main()
{
	char cmd1[] = "cat"; char *args1[] = {"cat", "Makefile", NULL};
	execvp(cmd1, args1);
	return (0);
}
