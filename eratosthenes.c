// eratosthenes.c
// Reseni IJC-DU1, priklad A), 18. 3. 2020
// Autor: David Hurta, FIT
// Prelozeno: gcc 7.5.0
// Zdrojovy soubor pro vypocet prvocisel pomoci Eratosthenova sita.
// Poznamky:	Vyuziva bitovou mapu ze souboru bitset.h

#include "eratosthenes.h"

void Eratosthenes(bitset_t array)
{
	if (array == NULL)
		error_exit("eratosthenes: Ukazatel pole je NULL");

	if (bitset_size(array) < 2)
		return;

	bitset_setbit(array, 0, 1);
	bitset_setbit(array, 1, 1);
	bitset_index_t N = bitset_size(array);

	unsigned long i = 2;
	double horniMez = sqrt(N);

	// Oznaceni sudych cisel
	unsigned long sumOfIncrements = i;
	while (sumOfIncrements < N)
	{
		bitset_setbit(array, sumOfIncrements, 1);
		sumOfIncrements += i;
	}
	i++;	

	// Oznaceni lichych nasobku (krome nasobku jedna) lichych cisel
	// Sude nasobky neni treba oznacovat, jsou to sude cisla, ktere jiz byla oznacena
	while (i <= horniMez)
	{
		if (bitset_getbit(array, i) == 1)
		{
		}
		else
		{
			sumOfIncrements = i + 2 * i;
			while (sumOfIncrements < N)
			{
				bitset_setbit(array, sumOfIncrements, 1);
				sumOfIncrements += 2 * i;
			}
		}
		i += 2;
	}
}
