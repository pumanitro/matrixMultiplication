// matrixMultiplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>


int main()
{
	//###Czytanie z pliku###

	//Deklaracja plików
	FILE *firstMatrixFile, *secondMatrixFile, *outputFile;

	//Zmienne do danych z plików {FM - FirstMatrix | SM - SecondMatrix}
	int FMRowLenght=0, FMColumnLenght=0, SMRowLenght=0, SMColumnLenght=0;
	float test=0;

	//Otwarcie plików do odczytu 
	if ((firstMatrixFile = fopen("firstMatrixFile.txt", "r")) == NULL) {
		printf("Nie mogê otworzyæ pliku firstMatrixFile.txt!\n");
		exit(1);
	}
	else if ((firstMatrixFile = fopen("secondMatrixFile.txt", "r")) == NULL) {
		printf("Nie mogê otworzyæ pliku secondMatrixFile.txt!\n");
		exit(1);
	}

	//Okreœlenie d³ugoœci wierszy i kolumn
	fscanf(firstMatrixFile, "%d", &FMRowLenght);
	fscanf(firstMatrixFile, "%d", &FMColumnLenght);
	fscanf(firstMatrixFile, "%d", &SMRowLenght);
	fscanf(firstMatrixFile, "%d", &SMColumnLenght);

	//Czytanie po ca³ych plikach
	while (fscanf(firstMatrixFile, "%f", &test)!=EOF)
	{
		printf("%f\n", test);
	}

	//fprintf(fp, "%s", tekst); /* zapisz nasz ³añcuch w pliku */
	fclose(firstMatrixFile); /* zamknij plik */


	printf("Pierwszy program w tym roku xD\n");
	system("pause");
    return 0;
}

