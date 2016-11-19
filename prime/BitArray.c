#include <stdlib.h>
#include <stdio.h>
#include "BitArray.h"

BitArray *initbarr(unsigned long long int length)
{
	unsigned long long int chunksize = (((length - 1) / 8) + 1) * sizeof(unsigned char);
	BitArray *t = (BitArray *) malloc(sizeof(BitArray));
	t->length = length;
	t->chunk = (unsigned char *) malloc(chunksize);
	return t;
}

void setallchunks(int bit, BitArray *barr)
{
	unsigned long long int i = 0;
	while (i < barr->length)
		setbitat(bit, i++, barr);
}

int getbitat(unsigned long long int p, BitArray *barr)
{
	return (barr->chunk[p/8] & (1 << (p % 8)))? 1 : 0;
}

void setbitat(int bit, unsigned long long int p, BitArray *barr)
{
	if (bit)
		barr->chunk[p/8] |= ((1 << (p % 8)) & 0xFF);
	else
		barr->chunk[p/8] &= ~((1 << (p % 8)) & 0xFF);
}

unsigned long long int countbit(int bit, BitArray *barr)
{
	unsigned long long int i = 0, c = 0;
	while (i < barr->length)
		c += (getbitat(i++, barr) == bit);
	return c;

}
