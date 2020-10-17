// bitset-i.c
// Reseni IJC-DU1, priklad A), 16. 3. 2020
// Autor: David Hurta, FIT
// Prelozeno: gcc 7.5.0
// Zdrojovy soubor pro deklaraci inline funkci.

#include "bitset.h"

extern void bitset_free(bitset_t jmeno_pole);

extern unsigned long bitset_size(bitset_t jmeno_pole);

extern void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, double vyraz);

extern int bitset_getbit(bitset_t pole, bitset_index_t index);
