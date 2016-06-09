#pragma once

#include "ErrorMSG.h"
#include "ErrorCodes.h"

using namespace std;

void showError(int state)
{
	switch (state)
	{
		case ERR_OPENING_FILE:
			std:cout << ERR_MSG_OPENING_FILE << endl;
			break;

	}
}

//-2 - podanych macierzy nie mo�na pomno�y�
//0 - wszystko posz�o zgodnie z planem - macierz pomno�ona
//RM - ResultMatrix
int matrixMultiplication(float **firstMatrix, float **secondMatrix, int FMRows, int FMColumns, int SMRows, int SMColumns, float **&resultMatrix, int *RMRows, int *RMColumns)
{
	//Sprawdzenie czy macierze mo�na mno�y�
	if (FMColumns != SMRows) return -2;

	//Stworzenie wymiar�w nowej macierzy
	*RMRows = FMRows;
	*RMColumns = SMColumns;

	//Alokacja pami�ci nowej macierzy
	resultMatrix = (float **)malloc(*RMRows*sizeof(float *));
	for (int i = 0; i < *RMRows; i++)
	{
		resultMatrix[i] = (float *)malloc(*RMColumns*sizeof(float));
	}

	//Przypisanie warto�ci do zaalokowanej tablicy
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

	return 0;
}

//0-Poprawnie zako�czona funkcja
//ErrorCode - -1 - Nie mog� otworzy� pliku
int openFile(FILE *&file, char name[], char type[])
{
	if ((file = fopen(name, type)) == NULL) return(-1);
	return(0);
}