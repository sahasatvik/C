
#ifndef _SIEVE_H
#define _SIEVE_H

/* Sieves a BitArray for primes, setting bits whose indices are composite numbes to 1 */
void sievebarr(BitArray *);

/* Displays primes contained in a BitArray */
void dispprimes(BitArray *);

/* Checks whether the specified number is prime, using data in the specified BitArray */
int chkprimebarr(unsigned long long int, BitArray *);

/* Returns the number of primes in the specified BitArray */
unsigned long long int countprimes(BitArray *);

#endif
