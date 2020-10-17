// ppm.c
// Reseni IJC-DU1, priklad B), 16. 3. 2020
// Autor: David Hurta, FIT
// Prelozeno: gcc 7.5.0
// Zdrojovy soubor pro zpracovani a overeni souboru typu .ppm

#include "ppm.h"

// Overuje soubor dle sablony 
// "P6<white space/s><integer type><white space/s><integer type><white space/s>255<white space/s><characters><EOF>"
int isFormatCorrect(const char * filename)
{
	const char * formatofFile = ".ppm";
	// Nazev souboru musi mit delku alespon peti znaku = *.ppm
	if (strlen(filename) < strlen(formatofFile) + 1)
		return 1;

	// Kontrola pripony souboru
	if (strcmp(&filename[strlen(filename)-strlen(formatofFile)], formatofFile) != 0)
		return 1;

	FILE *file;
	file = fopen(filename, "r");
	if (file == NULL)
		return 1;

	char str[4];
	int value;

	// Prvni dva znaky musi byt "P6"
	if ((value = fscanf(file, "%2s", str)) != 1 || value == EOF)
		goto closeFile_fail;

	if (strcmp(str, "P6") != 0)
		goto closeFile_fail;
	
	// Nasledne musi nasledovat alespon jeden bily znak
	if (isspace(value = fgetc(file)) == 0 || value == EOF)
		goto closeFile_fail;

	//Nasledne cislo
	int xsize = 0;
	if ((value = fscanf(file, "%d", &xsize)) != 1 || value == EOF)
		goto closeFile_fail;

	// Nasledne musi nasledovat alespon jeden bily znak
	if (isspace(value = fgetc(file)) == 0 || value == EOF)
		goto closeFile_fail;

	//Nasledne cislo
	int ysize = 0;
	if ((value = fscanf(file, "%d", &ysize)) != 1 || value == EOF)
		goto closeFile_fail;

	// Nasledne musi nasledovat alespon jeden bily znak
	if (isspace(value = fgetc(file)) == 0 || value == EOF)
		goto closeFile_fail;

	// Nasledne 255
	if ((value = fscanf(file, "%3s", str)) != 1 || value == EOF)
		goto closeFile_fail;

	if (strcmp(str, "255") != 0)
		goto closeFile_fail;

	// Nasledne musi nasledovat alespon jeden bily znak
	if (isspace(value = fgetc(file)) == 0 || value == EOF)
		goto closeFile_fail;

	// Oddeleni bilych znaku
	if ((value = fscanf(file, " ")) != 0 || value == EOF)
		goto closeFile_fail;

	if (xsize <= 0 || ysize <= 0 || xsize * ysize * 3 > MAX_VELIKOST_OBRAZ_DAT)
		goto closeFile_fail;

	// Kontrola poctu znaku
	int counter = 0;
	while (fgetc(file) != EOF)
		counter++;

	if (counter / 3.0 != xsize * ysize)
	{
		goto closeFile_fail;
	}
	else
	{
		fclose(file);
		return 0;
	}


	closeFile_fail:
		fclose(file);
		return 1;
}

struct ppm * ppm_read(const char * filename)
{
	if (isFormatCorrect(filename))
	{
		error_exit("ppm_read: Chybny format\n");
		return NULL;
	}

	FILE *file;
	file = fopen(filename, "r");

	if (file == NULL)
	{
		error_exit("ppm_read: Soubor nelze otevrit\n");
		return NULL;
	}

	int xsize = 0;
	int ysize = 0;
	if (fscanf(file, "P6 %d %d 255 ", &xsize, &ysize) != 2)
	{
		fclose(file);
		error_exit("ppm_read: Chybny format\n");
		return NULL;
	}

	struct ppm * pointerPPM = malloc(sizeof(struct ppm) + xsize * ysize * 3 * sizeof(char));
	if (pointerPPM == NULL)
	{
		fclose(file);
		error_exit("ppm_read: Chybna alokace pameti\n");
		return NULL;
	}

	pointerPPM->xsize = xsize;
	pointerPPM->ysize = ysize;

	int i = 0;
	int c = '0';
	while ((c = getc(file)) != EOF)
	{
		pointerPPM->data[i++] = c;
	}

	fclose(file);
	return pointerPPM;
}

void ppm_free(struct ppm *p)
{
	free(p);
	p = NULL;
}
