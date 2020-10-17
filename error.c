// error.c
// Reseni IJC-DU1, priklad B), 16. 3. 2020
// Autor: David Hurta, FIT
// Prelozeno: gcc 7.5.0
// Zdrojovy soubor pro oznamovani chyb pri behu programu, vypisu a ukonceni.

#include "error.h"

// Vytiskne na stderr chybove hlaseni dane parametrem
void warning_msg(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	fprintf(stderr, "CHYBA: ");
	vfprintf(stderr, fmt, args);
	va_end(args);
}

// Vytiskne na stderr chybove hlaseni dane parametrem a ukonci program funkci exit()
void error_exit(const char *fmt, ...)
{
	warning_msg(fmt);
	exit(1);
}

