// ppm.h
// Reseni IJC-DU1, priklad B), 16. 3. 2020
// Autor: David Hurta, FIT
// Prelozeno: gcc 7.5.0
// Hlavickovy soubor pro zpracovani a overeni souboru typu .ppm
// Poznamky:	Soubor obsahuje deklarace zakladnich funkci a definici datoveho typu ppm

#ifndef PPM_H
#define PPM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "error.h"

#define MAX_VELIKOST_OBRAZ_DAT 8000*8000*3

struct ppm {
	unsigned xsize;
	unsigned ysize;
	char data[];    // RGB bajty, celkem 3*xsize*ysize
};

// Nacte obsah PPM souboru do touto funkci dynamicky alokovane struktury
// Pri chybe formatu pouzije funkci warning_msg a vrati NULL.
struct ppm * ppm_read(const char * filename);

// Uvolní pamet dynamicky alokovanou v ppm_read
void ppm_free(struct ppm *p);

// Overi zda formatu souboru splnuje podminky souboru ppm
// V pripade, ze format je spravny, vrati 1, jinak 0
int isFormatCorrect(const char * filename);

#endif // PPM_H
