// matrixMultiplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>


int main()
{
	//###Czytanie z pliku###

	//Deklaracja plik�w
	FILE *firstMatrixFile, *secondMatrixFile, *outputFile;

	//Zmienne do danych z plik�w {FM - FirstMatrix | SM - SecondMatrix}
	int FMRows=0, FMColumns=0, SMRows=0, SMColumns=0;

	//Otwarcie plik�w do odczytu 
	if ((firstMatrixFile = fopen("firstMatrixFile.txt", "r")) == NULL) {
		printf("Nie mog� otworzy� pliku firstMatrixFile.txt!\n");
		exit(1);
	}
	if ((secondMatrixFile = fopen("secondMatrixFile.txt", "r")) == NULL) {
		printf("Nie mog� otworzy� pliku secondMatrixFile.txt!\n");
		exit(1);
	}

	//Okre�lenie d�ugo�ci wierszy i kolumn
	fscanf(firstMatrixFile, "%d", &FMRows);
	fscanf(firstMatrixFile, "%d", &FMColumns);
	fscanf(secondMatrixFile, "%d", &SMRows);
	fscanf(secondMatrixFile, "%d", &SMColumns);

	//Alokacja pami�ci
	//First matrix
	float **firstMatrix = (float **)malloc(FMRows*sizeof(float *));
	for (int i = 0; i < FMColumns; i++)
	{
		firstMatrix[i] = (float *)malloc(FMColumns*sizeof(float));
	}

	//Second matrix
	float **secondMatrix = (float **)malloc(SMRows*sizeof(float *));
	for (int i = 0; i < SMColumns; i++)
	{
		secondMatrix[i] = (float *)malloc(SMColumns*sizeof(float));
	}

	//Czytanie po ca�ych plikach i zapisanie danych do odpowiednich zmiennych
	//First Matrix
	for (int i = 0; i < FMRows; i++)
	{
		for (int j = 0; j < FMColumns; j++)
		{
			fscanf(firstMatrixFile, "%f", &firstMatrix[i][j]);
			printf("%f ", firstMatrix[i][j]);
		}
		printf("\n");
	}

	//Second Matrix
	for (int i = 0; i < SMRows; i++)
	{
		for (int j = 0; j < SMColumns; j++)
		{
			fscanf(secondMatrixFile, "%f", &secondMatrix[i][j]);
			printf("%f ", secondMatrix[i][j]);
		}
		printf("\n");
	}

	//fprintf(fp, "%s", tekst); /* zapisz nasz �a�cuch w pliku */

	//Zamkni�cie plik�w
	fclose(firstMatrixFile); 
	fclose(secondMatrixFile);

	system("pause");
    return 0;
}

