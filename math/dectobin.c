#include <stdlib.h>
#include <stdio.h>

typedef unsigned long long int Long;

#define MAXSIZE 100

Long numbers[MAXSIZE];

int  getnum(Long *, int, const char **);
void printbin(Long dec);

/* Converts the numbers in the command line into binary */
int main(int argc, char const *argv[]) {
        int i;
        int size = getnum(numbers, argc, argv);
        for (i = 0; i < size; i++) {
                printbin(numbers[i]);
        }
        return 0;
}

int getnum(Long *target, int argc, const char *argv[])
{
        Long n;
        int size;
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

void printbin(Long dec)
{
        int pow;
        for (pow = 0; dec >> pow; pow++);
        for (; pow >= 0; pow--)
                printf("%d", (int) ((dec >> pow) & 1));
        printf(" ");
}
