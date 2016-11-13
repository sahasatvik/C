#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


int  getnum(int *, int, const char **);

int main(int argc, const char *argv[])
{
	int i, number, max;
	int args[100];
	getnum(args, argc, argv);
	number = (args[0])? args[0] : 10;
	max    = (args[1])? args[1] : 100;
	for(i = 0; i < number; i++)
		printf("%d ", rand() % max);
	return 0;
}

int getnum(int *target, int argc, const char *argv[])
{
	int size, n;
	const char *arg;
	size = 0;
	while(--argc)
		if(isdigit(*(arg = *++argv)))
		{
			n = 0;
			while(isdigit(*arg))
				n = (n * 10) + (*arg++ - '0');
			target[size++] = n;
		}
	return size;
}
