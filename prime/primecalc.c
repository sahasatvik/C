#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "BitArray.h"
#include "Sieve.h"

typedef unsigned long long int Long;

Long getsize(int, const char **);
int  hasflag(char, int, const char **);
void help();

/* Generates a list of prime numbers, storage efficient version */
int main(int argc, const char *argv[])
{
	int size = getsize(argc, argv);
	if (size < 1 || hasflag('h', argc, argv))
		help();
	BitArray *numbers = initbarr(1 + size);
	sievebarr(numbers);
	if (hasflag('c', argc, argv))
		printf("%llu", countprimes(numbers));
	else
		dispprimes(numbers);
	printf("\n");
	return 0;
}

void help()
{
	printf("%s\n%s\n%s\n%s\n%s\n",
			"Primecalc : 	calculates prime numbers upto the value specified.\n",
			"Usage     :	primecalc [-h] [-c] max_value\n",
			"Options   : 	",
			"	-h	:	Display this help message",
			"	-c	:	Show only the number of primes calculated");
	exit(0);
}

Long getsize(int argc, const char *argv[])
{
	Long size = 0;
	const char *arg;
	while (--argc > 0) {
		if (isdigit(*(arg = *++argv))) {
			while (isdigit(*arg))
				size = (10 * size) + (*arg++ - '0');
			return size;
		}
	}
	return 0;
}

int hasflag(char c, int argc, const char *argv[])
{
	const char *arg = "";
	while (--argc > 0)
		if ((*(arg = *++argv) == '-') && (*++arg == c))
			return 1;
	return 0;
}
