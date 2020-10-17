// bitset.h
// Reseni IJC-DU1, priklad A), 16. 3. 2020
// Autor: David Hurta, FIT
// Prelozeno: gcc 7.5.0
// Hlavickovy soubor pro praci s bitovym polem.
// Poznamky:	Makra bitset_create a bitset_alloc se definuji pri prekladu.
// 		Nasledne se definuji bud makra, nebo inline funkce. Dle definice USE_INLINE.

#ifndef BITSET_H
#define BITSET_H

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include "error.h"

// Typ bitoveho pole (pro predavvni parametru do funkce odkazem).
typedef unsigned long* bitset_t;

// Typ indexu do bitoveho pole.
typedef unsigned long bitset_index_t;

// Vyctovy datovy typ pro vraceni hodnot pri nalezu chyby
enum errors{ERROR_OUT_OF_BOUNDS = 2, ERROR_ALLOC = 3};

// Definuje a _nuluje_ promennou jmeno_pole
#define bitset_create(jmeno_pole, velikost)\
		bitset_index_t jmeno_pole[(bitset_index_t)(1 + (((velikost) / (CHAR_BIT*(sizeof(unsigned long))) + (velikost) % (CHAR_BIT*(sizeof(unsigned long))) == 0) ? ((velikost) / (CHAR_BIT*(sizeof(unsigned long)))) : ((velikost) / (CHAR_BIT*(sizeof(unsigned long))) + 1)))] = {0};\
		static_assert(((velikost) > 1) && ((velikost) <= ULONG_MAX), "bitset_create: Chyba velikosti pole\n");\
		jmeno_pole[0] = (velikost);\

// Definuje a nuluje promennou jmeno_pole, pole bude alokovano dynamicky.
#define bitset_alloc(jmeno_pole, velikost)\
		bitset_t jmeno_pole = malloc((1 + ceil((double)(velikost) / (CHAR_BIT*(sizeof(unsigned long))))) * sizeof(unsigned long));\
		assert(((velikost) > 1) && ((velikost) <= ULONG_MAX));\
		if (jmeno_pole == NULL)\
		{\
			fprintf(stderr, "bitset_alloc: Chyba alokace paměti\n");\
			exit(EXIT_FAILURE);\
		}\
		jmeno_pole[0] = 1 + ceil((double)(velikost) / (CHAR_BIT*(sizeof(unsigned long))));\
		for (unsigned long i = 1; i < jmeno_pole[0]; i++)\
			jmeno_pole[i] = 0;\
		jmeno_pole[0] = (velikost);


#ifndef USE_INLINE
// -------------------------	Varianta s makry	-------------------------

// Uvolni pamet dynamicky alokovaneho pole a nastavi ukazatek pole na NULL
#define bitset_free(jmeno_pole)\
	do {\
		free(jmeno_pole);\
		jmeno_pole = NULL;\
	} while(0)

// Vrati deklarovanou velikost pole v bitech (ulozenou v poli)
#define bitset_size(jmeno_pole) ((jmeno_pole) != NULL ? jmeno_pole[0] : 0)

// Nastavi zadany bit v poli na hodnotu zadanou vyrazem
// (nulovy vyraz == bit 0, nenulovy vyraz == bit 1)
#define bitset_setbit(jmeno_pole, index, vyraz)\
	do {\
		if (jmeno_pole != NULL)\
		{\
			if ((unsigned long)(index) >= jmeno_pole[0])\
			{\
				error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu\n", (unsigned long)(index), (unsigned long)(jmeno_pole[0] - 1));\
			}\
			else if ((vyraz) == 0)\
			{\
				jmeno_pole[(index)/(CHAR_BIT*(sizeof(unsigned long))) + 1] = jmeno_pole[(index)/(CHAR_BIT*(sizeof(unsigned long))) + 1] & ~(1UL << ((index)%(CHAR_BIT*(sizeof(unsigned long)))));\
			}\
			else\
			{\
				jmeno_pole[(index)/(CHAR_BIT*(sizeof(unsigned long))) + 1] = jmeno_pole[(index)/(CHAR_BIT*(sizeof(unsigned long))) + 1] | (1UL << ((index)%(CHAR_BIT*(sizeof(unsigned long)))));\
			}\
		}\
	} while(0)\

// Ziska hodnotu zadaneho bitu, vraci hodnotu 0 nebo 1
// V pripade chyby vraci hodnotu vetsi nez 1
#define bitset_getbit(jmeno_pole, index) ((jmeno_pole) != NULL ? (((unsigned long)(index) < jmeno_pole[0]) ? (((jmeno_pole[(index)/(CHAR_BIT*(sizeof(unsigned long))) + 1] & (1UL << ((index)%(CHAR_BIT*(sizeof(unsigned long)))))) == 0) ? 0 : 1) : (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n", (unsigned long)(index), (unsigned long)(jmeno_pole[0] - 1)),ERROR_OUT_OF_BOUNDS)) : ERROR_ALLOC)

#else
//--------------------------	USE_INLINE	-------------------------

// Uvolni pamet dynamicky alokovaneho pole
inline void bitset_free(bitset_t jmeno_pole)
{
	free(jmeno_pole);
	jmeno_pole = NULL;
}

// Vrati deklarovanou velikost pole v bitech (ulozenou v poli)
inline unsigned long bitset_size(bitset_t jmeno_pole)
{
	return ((jmeno_pole) != NULL ? jmeno_pole[0] : 0);
}

// Nastavi zadany bit v poli na hodnotu zadanou vyrazem
// (nulovy vyraz == bit 0, nenulovy vyraz == bit 1)
inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, double vyraz)
{
	if (jmeno_pole != NULL)
	{
		if ((unsigned long)(index) >= jmeno_pole[0])
		{
			error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu\n", (unsigned long)(index), (unsigned long)(jmeno_pole[0] - 1));
		}
		else if ((vyraz) == 0)
		{
			jmeno_pole[(index)/(CHAR_BIT*(sizeof(unsigned long))) + 1] = jmeno_pole[(index)/(CHAR_BIT*(sizeof(unsigned long))) + 1] & ~(1UL << ((index)%(CHAR_BIT*(sizeof(unsigned long)))));
		}
		else
		{
			jmeno_pole[(index)/(CHAR_BIT*(sizeof(unsigned long))) + 1] = jmeno_pole[(index)/(CHAR_BIT*(sizeof(unsigned long))) + 1] | (1UL << ((index)%(CHAR_BIT*(sizeof(unsigned long)))));
		}
	}
}

// Ziska hodnotu zadaneho bitu, vraci hodnotu 0 nebo 1
// V pripade chyby vraci hodnotu vetsi nez 1 (viz enum errors)
inline int bitset_getbit(bitset_t pole, bitset_index_t index)
{
	if (pole != NULL)
	{
		if (index < pole[0])
		{
			if ((pole[index/(CHAR_BIT*sizeof(bitset_index_t)) + 1] & (1UL << (index % (CHAR_BIT * sizeof(bitset_index_t))))) == 0)
			{
				return 0; 
			}
			else
			{
				return 1;
			}
		}
		else
		{
			error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n", (unsigned long)(index), (unsigned long)(pole[0] - 1));
			return ERROR_ALLOC;
		}
	}
	else
	{
		error_exit("bitset_getbit: Ukazatel na bitset je NULL\n");
		return ERROR_OUT_OF_BOUNDS;
	}
}

#endif // USE_INLINE
#endif // BITSET_H
