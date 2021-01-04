
#ifndef _BITARR_H
#define _BITARR_H

/* Defines a simulated array of bits */
typedef struct {
	unsigned long long int length;
	unsigned char *chunk;
} BitArray;


/* Returns the address of a new BitArray, as defined in BitArray.h */
BitArray *initbarr(unsigned long long int);

/* Sets all bits of the specified BitArray to the specified value */
void setallchunks(int, BitArray *);

/* Returns the bit at the specified posiotion */
int getbitat(unsigned long long int, BitArray *);

/* Sets a bit at the specified position */
void setbitat(int, unsigned long long int, BitArray *);

/* Returns the number of all occurrences of the specified bit in the specified BitArray */
unsigned long long int countbit(int, BitArray *);

#endif
