#include <stdio.h>
#include "BitArray.h"
#include "Sieve.h"

void sievebarr(BitArray *numbers)
{
	unsigned long long int m, n = 2;
	setallchunks(0, numbers);
	setbitat(1, 0, numbers);
	setbitat(1, 1, numbers);
	while ((n * n) < numbers->length) {
		m = n;
		while ((m = m + n) < numbers->length)
			setbitat(1, m, numbers);
		while (getbitat(++n, numbers));
	}
}

void dispprimes(BitArray *numbers)
{
	unsigned long long int i = 0;
	for (i = 0; i < numbers->length; i++)
		if (chkprimebarr(i, numbers))
			printf("%llu ", i);
}

int chkprimebarr(unsigned long long int p, BitArray *numbers)
{
	return !getbitat(p, numbers);
}

unsigned long long int countprimes(BitArray *numbers)
{
	return countbit(0, numbers);
}
