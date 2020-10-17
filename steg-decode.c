// steg-decode.c
// Reseni IJC-DU1, priklad B), 19. 3. 2020
// Autor: David Hurta, FIT
// Prelozeno: gcc 7.5.0
// Zdrojovy soubor pro dekodovani skryte zpravy ve zprave souboru .ppm ve formatu P6.

#include <stdlib.h>
#include "ppm.h"
#include "error.h"
#include "bitset.h"
#include "eratosthenes.h"

#define STARTING_PRIME_NUMBER 23

int main(int argc, char *argv[])
{
	// Kontrola argumentu
	if (argc != 2)
	{
		error_exit("steg-decode.c: Spatny pocet argumentu\n");
	}

	struct ppm * ppmVariable = ppm_read(argv[1]);

	if (ppmVariable == NULL)
	{
		error_exit("steg-decode.c: Chybny format\n");
	}

	// Definice promennych
	bitset_alloc(bitsetArray, ppmVariable->xsize * ppmVariable->ysize * 3 * CHAR_BIT);
	Eratosthenes(bitsetArray);

	int secretMessageSize = 1;
	int numberOfChars = 0; 
	char * secretMessage = NULL;
	char * strPointer = NULL;
	int mask = 1;
	int counter = 0;
	char character = '0';
	unsigned long sizeOfPicture = ppmVariable->xsize * ppmVariable->ysize;
	unsigned long i = STARTING_PRIME_NUMBER;

	character ^= character;

	// Alokace pameti pro tajnou zpravu, zacina se na jednom znaku
	secretMessage = malloc(sizeof(char)*secretMessageSize);
	if (secretMessage == NULL)
	{
		bitset_free(bitsetArray);
		ppm_free(ppmVariable);
		error_exit("steg-decode: Chybna alokace pameti\n");
	}

	// Desifrovani
	while (i < sizeOfPicture)
	{
		if (bitset_getbit(bitsetArray, i) == 0)
		{
			// Zapisovani bitu vybraneho bajtu do noveho znaku
			if (ppmVariable->data[i] & 1UL)
			{
				character = character | mask;
			}
			else
			{
				character = character & ~(mask);
			}
			mask = mask<<1;
			counter++;

			// Ulozeni hotoveho znaku
			if (counter == CHAR_BIT)
			{
				numberOfChars++;

				// Po dosazeni limitu velikosti alokovane pameti, se pamet zdvojnasobi
				if (numberOfChars > secretMessageSize)
				{
					secretMessageSize *= 2;
					strPointer = secretMessage;
					secretMessage = realloc(secretMessage, sizeof(char)*secretMessageSize);
					if (secretMessage == NULL)
					{
						free(strPointer);
						bitset_free(bitsetArray);
						ppm_free(ppmVariable);
						error_exit("steg-decode: Chybna alokace pameti\n");
					}
				}

				// Zapis noveho znaku a kontrola, zda se jedna o ukoncovaci znak
				secretMessage[numberOfChars - 1] = character;
				if (character == '\0')
				{
					break;
				}

				counter = 0;
				mask = 1;
				character ^= character;				
			}
		}
		i++;
	}

	// V pripade, ze posledni znak byl ukoncovaci, tajna zprava se vytiskne
	if (numberOfChars == 0 || secretMessage[numberOfChars - 1] != '\0')
	{
		free(secretMessage);
		bitset_free(bitsetArray);
		ppm_free(ppmVariable);
		error_exit("steg-decode.c: Chybny format\n");
	}
	else
	{
		printf("%s\n", secretMessage);
	}

	free(secretMessage);
	bitset_free(bitsetArray);
	ppm_free(ppmVariable);
	return 0;
}
