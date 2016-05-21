// matrixMultiplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>


int main()
{
	//Czytanie z pliku
	//Deklaracja plik�w
	FILE *firstMatrixFile, *secondMatrixFile, *outputFile;

	//Zmienne do danych z plik�w {FM - FirstMatrix | SM - SecondMatrix}
	int FMRowLenght, FMColumnLenght, SMRowLenght, SMColumnLenght;
	char test[5];

	//Otwarcie plik�w do odczytu 
	if ((firstMatrixFile = fopen("firstMatrixFile.txt", "r")) == NULL) {
		printf("Nie mog� otworzy� pliku firstMatrixFile.txt!\n");
		exit(1);
	}
	else if ((firstMatrixFile = fopen("secondMatrixFile.txt", "r")) == NULL) {
		printf("Nie mog� otworzy� pliku secondMatrixFile.txt!\n");
		exit(1);
	}

	//Czytanie po ca�ych plikach
	while (fscanf(firstMatrixFile, "%s", test)!=EOF)
	{
		printf("%s", test);
	}

	//fprintf(fp, "%s", tekst); /* zapisz nasz �a�cuch w pliku */
	fclose(firstMatrixFile); /* zamknij plik */


	printf("Pierwszy program w tym roku xD\n");
	system("pause");
    return 0;
}

