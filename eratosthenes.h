// eratosthenes.h
// Reseni IJC-DU1, priklad A), 18. 3. 2020
// Autor: David Hurta, FIT
// Prelozeno: gcc 7.5.0
// Hlavickovy soubor pro zdrojovy soubor eratosthenes.h.c

#ifndef ERATOSTHENES_H
#define ERATOSTHENES_H

#include <math.h>
#include "bitset.h"
#include "error.h"

// Vyznaci v bitove mape prvocisla
// Prvocisla jsou znacena 0, ostatni cisla jsou znacena 1
void Eratosthenes(bitset_t pole);

#endif // ERATOSTHENES_H
