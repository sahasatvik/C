#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int  getnum(int *, int, const char **);

/* Generates a list of random numbers */
int main(int argc, const char *argv[])
{
	int i, number = 10, max = 100;
	int args[100];
	int size = getnum(args, argc, argv);
        if (size > 0)
                number = args[0];
        if (size > 1)
                max = args[1];
	for (i = 0; i < number; i++)
		printf("%d ", rand() % max);
	return 0;
}

int getnum(int *target, int argc, const char *argv[])
{
	int size, n;
	const char *arg;
	size = 0;
	while (--argc)
		if (isdigit(*(arg = *++argv))) {
			n = 0;
			while (isdigit(*arg))
				n = (n * 10) + (*arg++ - '0');
			target[size++] = n;
		}
	return size;
}
