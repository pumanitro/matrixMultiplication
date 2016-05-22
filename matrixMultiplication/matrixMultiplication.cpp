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
	if ((secondMatrixFile = fopen("secondMatrixFile.txt", "r")) == NULL) {
		printf("Nie mogê otworzyæ pliku secondMatrixFile.txt!\n");
		exit(1);
	}

	//Okreœlenie d³ugoœci wierszy i kolumn
	fscanf(firstMatrixFile, "%d", &FMRowLenght);
	fscanf(firstMatrixFile, "%d", &FMColumnLenght);
	fscanf(secondMatrixFile, "%d", &SMRowLenght);
	fscanf(secondMatrixFile, "%d", &SMColumnLenght);

	//Alokacja pamiêci
	//First matrix
	float **firstMatrix = (float **)malloc(FMRowLenght*sizeof(float *));
	for (int i = 0; i < FMColumnLenght; i++)
	{
		firstMatrix[i] = (float *)malloc(FMColumnLenght*sizeof(float));
	}

	//Second matrix
	float **secondMatrix = (float **)malloc(SMRowLenght*sizeof(float *));
	for (int i = 0; i < SMColumnLenght; i++)
	{
		secondMatrix[i] = (float *)malloc(SMColumnLenght*sizeof(float));
	}

	//Czytanie po ca³ych plikach i zapisanie danych do odpowiednich zmiennych
	for (int i = 0; i < FMRowLenght; i++)
	{
		for (int j = 0; j < FMColumnLenght; j++)
		{
			fscanf(firstMatrixFile, "%f", &firstMatrix[i][j]);
			printf("%f ", firstMatrix[i][j]);
		}
		printf("\n");
	}

	//fprintf(fp, "%s", tekst); /* zapisz nasz ³añcuch w pliku */

	//Zamkniêcie plików
	fclose(firstMatrixFile); 
	fclose(secondMatrixFile);

	system("pause");
    return 0;
}

