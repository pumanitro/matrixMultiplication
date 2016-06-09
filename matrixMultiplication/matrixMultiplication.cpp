// matrixMultiplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "Functions.h"
#include "ErrorMSG.h"
#include "ErrorCodes.h"

using namespace std;
#define OK 0

int main()
{
	//###Czytanie z pliku###

	//Deklaracja plik�w
	FILE *firstMatrixFile, *secondMatrixFile, *outputFile;

	//Zmienne do danych z plik�w {FM - FirstMatrix | SM - SecondMatrix}
	int FMRows=0, FMColumns=0, SMRows=0, SMColumns=0;

	//Deklaracja stanu dla sprawdzania errorCodes
	int state;

	//Otwarcie plik�w 
	state = openFile(firstMatrixFile, "firstMatrixFile.txt", "r");
	if (state != OK) showError(state);
	state = openFile(secondMatrixFile, "secondMatrixFile.txt", "r");
	if (state != OK) showError(state);
	state = openFile(outputFile, "resultMatrix.txt", "w");
	if (state != OK) showError(state);

	//Okre�lenie d�ugo�ci wierszy i kolumn
	state = getRowsAndColsSize(firstMatrixFile, secondMatrixFile, &FMRows, &FMColumns, &SMRows, &SMColumns);
	if (state != OK) showError(state);

	//Alokacja pami�ci
	float **firstMatrix = 0, **secondMatrix = 0;

	matrixMemoryAlocation(firstMatrix,FMRows,FMColumns);
	matrixMemoryAlocation(secondMatrix, SMRows, SMColumns);

	//Czytanie po ca�ych plikach i zapisanie danych do odpowiednich tablic
	//First Matrix
	printf("First matrix:\n");
	for (int i = 0; i < FMRows; i++)
	{
		for (int j = 0; j < FMColumns; j++)
		{
			fscanf(firstMatrixFile, "%f", &firstMatrix[i][j]);
			printf("%.2f ", firstMatrix[i][j]);
		}
		printf("\n");
	}

	//Second Matrix
	printf("\nSecond matrix:\n");
	for (int i = 0; i < SMRows; i++)
	{
		for (int j = 0; j < SMColumns; j++)
		{
			fscanf(secondMatrixFile, "%f", &secondMatrix[i][j]);
			printf("%.2f ", secondMatrix[i][j]);
		}
		printf("\n");
	}

	//MNO�ENIE
	float **resultMatrix = 0;
	int RMRows = 0, RMColumns = 0;
	matrixMultiplication(firstMatrix, secondMatrix, FMRows, FMColumns, SMRows, SMColumns, resultMatrix, &RMRows, &RMColumns);

	//Zapisanie wyniku do pliku
	//Wpisanie wymiar�w macierzy do pliku
	fprintf(outputFile, "%d ", RMRows);
	fprintf(outputFile, "%d\n", RMColumns);

	//Zapisanie zawarto�� macierzy
	for (int i = 0; i < RMRows; i++)
	{
		for (int j = 0; j < RMColumns; j++)
		{
			//TODO: THIS PART DONT WORK
			fprintf(outputFile, "%.2f ", resultMatrix[i][j]);
		}
		fprintf(outputFile, "\n");
	}

	//fprintf(fp, "%s", tekst); /* zapisz nasz �a�cuch w pliku */

	//Zwolnienie pami�ci
	//First matrix
	for (int i = 0; i < FMRows; i++)
	{
		free(firstMatrix[i]);
	}
	free(firstMatrix);

	//Second matrix
	for (int i = 0; i < SMRows; i++)
	{
		free(secondMatrix[i]);
	}
	free(secondMatrix);

	//Output matrix
	for (int i = 0; i < RMRows; i++)
	{
		free(resultMatrix[i]);
	}
	free(resultMatrix);

	//Zamkni�cie plik�w
	fclose(firstMatrixFile);
	fclose(secondMatrixFile);
	fclose(outputFile);

	system("pause");
    return 0;
}

