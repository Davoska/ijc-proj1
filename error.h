// error.h
// Reseni IJC-DU1, priklad B), 16. 3. 2020
// Autor: David Hurta, FIT
// Prelozeno: gcc 7.5.0
// Hlavickovy soubor pro oznamovani chyb pri behu programu, vypisu a ukonceni.

#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

// Tiskne chybove hlaseni podle formatu fmt s predponou "CHYBA " do stderr
void warning_msg(const char *fmt, ...);

// Tiskne chybove hlaseni podle formatu fmt s predponou "CHYBA " do stderr
// Ukonci program volanim funkce exit(1).
void error_exit(const char *fmt, ...);

#endif // ERROR_H
