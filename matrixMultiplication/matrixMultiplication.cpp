// matrixMultiplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

//0 - podanych macierzy nie mo¿na pomno¿yæ
//1 - wszystko posz³o zgodnie z planem - macierz pomno¿ona
//RM - ResultMatrix
int matrixMultiplication(float **firstMatrix, float **secondMatrix, int FMRows, int FMColumns, int SMRows, int SMColumns, float **resultMatrix, float *RMRows, float *RMColumns)
{
	//Sprawdzenie czy macierze mo¿na mno¿yæ
	if (FMColumns != SMRows) return 0;

	//Stworzenie wymiarów nowej macierzy
	*RMRows = FMRows;
	*RMColumns = SMColumns;

	//Alokacja pamiêci nowej macierzy
	resultMatrix = (float **)malloc(*RMRows*sizeof(float *));
	for (int i = 0; i < *RMRows; i++)
	{
		resultMatrix[i] = (float *)malloc(*RMColumns*sizeof(float));
	}

	//Przypisanie wartoœci do zaalokowanej tablicy
	printf("\nResult matrix:\n");
	int link = FMColumns;
	float out;

	for (int i = 0; i < *RMRows; i++)
	{
		for (int j = 0; j < *RMColumns; j++)
		{
			out = 0;
			for (int x = 0; x < link; x++)
			{
				out += firstMatrix[i][x] * secondMatrix[x][j];
			}
			resultMatrix[i][j] = out;
			printf("%.2f ", resultMatrix[i][j]);
		}
		printf("\n");
	}

	return 1;
}

int main()
{
	//###Czytanie z pliku###

	//Deklaracja plików
	FILE *firstMatrixFile, *secondMatrixFile, *outputFile;

	//Zmienne do danych z plików {FM - FirstMatrix | SM - SecondMatrix}
	int FMRows=0, FMColumns=0, SMRows=0, SMColumns=0;

	//Otwarcie plików do odczytu 
	if ((firstMatrixFile = fopen("firstMatrixFile.txt", "r")) == NULL) {
		printf("Nie mogê otworzyæ pliku firstMatrixFile.txt!\n");
		exit(1);
	}
	if ((secondMatrixFile = fopen("secondMatrixFile.txt", "r")) == NULL) {
		printf("Nie mogê otworzyæ pliku secondMatrixFile.txt!\n");
		exit(1);
	}
	if ((outputFile = fopen("resultMatrix.txt", "w")) == NULL) {
		printf("Nie mogê otworzyæ pliku resultMatrix.txt!\n");
		exit(1);
	}

	//Okreœlenie d³ugoœci wierszy i kolumn
	fscanf(firstMatrixFile, "%d", &FMRows);
	fscanf(firstMatrixFile, "%d", &FMColumns);
	fscanf(secondMatrixFile, "%d", &SMRows);
	fscanf(secondMatrixFile, "%d", &SMColumns);

	//Alokacja pamiêci
	//First matrix
	float **firstMatrix = (float **)malloc(FMRows*sizeof(float *));
	for (int i = 0; i < FMRows; i++)
	{
		firstMatrix[i] = (float *)malloc(FMColumns*sizeof(float));
	}

	//Second matrix
	float **secondMatrix = (float **)malloc(SMRows*sizeof(float *));
	for (int i = 0; i < SMRows; i++)
	{
		secondMatrix[i] = (float *)malloc(SMColumns*sizeof(float));
	}

	//Czytanie po ca³ych plikach i zapisanie danych do odpowiednich tablic
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

	//MNO¯ENIE
	float **resultMatrix;
	float RMRows = 0, RMColumns = 0;
	matrixMultiplication(firstMatrix, secondMatrix, FMRows, FMColumns, SMRows, SMColumns, resultMatrix, &RMRows, &RMColumns);

	//Zapisanie wyniku do pliku
	//Wpisanie wymiarów macierzy do pliku
	fprintf(outputFile, "%d ", RMRows);
	fprintf(outputFile, "%d", RMColumns);

	//Zapisanie zawartoœæ macierzy
	for (int i = 0; i < RMRows; i++)
	{
		for (int j = 0; j < RMColumns; j++)
		{
			//TODO: THIS PART DONT WORK
			fprintf(outputFile, "%.2f", RMRows);
		}
		fprintf(outputFile, "\n");
	}

	//fprintf(fp, "%s", tekst); /* zapisz nasz ³añcuch w pliku */

	//Zwolnienie pamiêci
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

	//Zamkniêcie plików
	fclose(firstMatrixFile);
	fclose(secondMatrixFile);
	fclose(outputFile);

	system("pause");
    return 0;
}

