#pragma once

#include "ErrorMSG.h"
#include "ErrorCodes.h"

using namespace std;

void showError(int state)
{
	switch (state)
	{
		case ERR_OPENING_FILE:
			std::cout << ERR_MSG_OPENING_FILE << endl;
			break;
		case ERR_GETING_ROWS_COLS_SIZE:
			std::cout << ERR_MSG_GETING_ROWS_COLS_SIZE << endl;
				break; 
		case ERR_MATRIX_ALOCATION:
			std::cout << ERR_MSG_MATRIX_ALOCATION << endl;
			break;
	}
}

//-2 - podanych macierzy nie mo¿na pomno¿yæ
//0 - wszystko posz³o zgodnie z planem - macierz pomno¿ona
//RM - ResultMatrix
int matrixMultiplication(float **firstMatrix, float **secondMatrix, int FMRows, int FMColumns, int SMRows, int SMColumns, float **&resultMatrix, int *RMRows, int *RMColumns)
{
	//Sprawdzenie czy macierze mo¿na mno¿yæ
	if (FMColumns != SMRows) return -2;

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

	return 0;
}

//0-Poprawnie zakoñczona funkcja
//ErrorCode - -1 - Nie mogê otworzyæ pliku
int openFile(FILE *&file, char name[], char type[])
{
	if ((file = fopen(name, type)) == NULL) return(-1);
	return(0);
}

//0-Poprawnie zakoñczona funkcja
//ErrorCode - -2 - Nie mogê prawid³owo odczytaæ kolumn lub wierszy
int getRowsAndColsSize(FILE *firstMatrixFile, FILE *secondMatrixFile, int *FMRows, int *FMColumns, int *SMRows, int *SMColumns)
{
	if (fscanf(firstMatrixFile, "%d", FMRows) == EOF ) return(-2);
	if (fscanf(firstMatrixFile, "%d", FMColumns) == EOF) return(-2);
	if (fscanf(secondMatrixFile, "%d", SMRows) == EOF) return(-2);
	if (fscanf(secondMatrixFile, "%d", SMColumns) == EOF) return(-2);

	return(0);
}

//0-Poprawnie zakoñczona funkcja
//ErrorCode - -3 - Problem z alokacj¹ pamiêci dla macierzy 
int matrixMemoryAlocation(float **&matrix, int rowNumber, int colNumber)
{
	try {
		matrix = (float **)malloc(rowNumber*sizeof(float *));
		for (int i = 0; i < rowNumber; i++)
		{
			matrix[i] = (float *)malloc(colNumber*sizeof(float));
		}
	}
	catch (...) { return(-3); }

	return 0;
}