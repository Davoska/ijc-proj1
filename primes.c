// primes.c
// Reseni IJC-DU1, priklad A), 18. 3. 2020
// Autor: David Hurta, FIT
// Prelozeno: gcc 7.5.0
// Zdrojovy soubor pro vypis prvocisel implementovanych bitovou mapou.

#include <stdio.h>
#include <time.h>
#include "bitset.h"
#include "eratosthenes.h"

#define N 500000000
#define NUMBER_OF_LAST_PRIME_NUMBERS_TO_PRINT 10

// Vytiksne poslednich maximalne N prvocisel
void printLastPrimeNumbers(bitset_t array, unsigned long nPrimeNumbers)
{
	bitset_index_t size = bitset_size(array);
	bitset_index_t k = 0;
	bitset_index_t i = 0;

	for (i = size - 1; i >= 2; i--)
	{
		if (bitset_getbit(array, i) == 0)
			k++;

		if (k == nPrimeNumbers)
			break;
	}

	for (i = i; i <= size - 1; i++)
	{
		if (bitset_getbit(array, i) == 0)
		{
			printf("%lu\n", i);
		}
	}
}

int main()
{
	clock_t start = clock();

	bitset_create(array, N);
	Eratosthenes(array);
	printLastPrimeNumbers(array, NUMBER_OF_LAST_PRIME_NUMBERS_TO_PRINT);

	fprintf(stderr, "Time=%.3g\n", (double)(clock() - start)/CLOCKS_PER_SEC);
	return 0;
}
