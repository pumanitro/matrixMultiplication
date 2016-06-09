#pragma once

#include "ErrorMSG.h"
#include "ErrorCodes.h"
#include <vector>

using namespace std;

void showError(int state)
{
	switch (state)
	{
		case ERR_OPENING_FILE:
			std::cout << endl << ERR_MSG_OPENING_FILE << endl;
			break;
		case ERR_GETING_ROWS_COLS_SIZE:
			std::cout << endl << ERR_MSG_GETING_ROWS_COLS_SIZE << endl;
			break; 
		case ERR_MATRIX_ALOCATION:
			std::cout << endl << ERR_MSG_MATRIX_ALOCATION << endl;
			break; 
		case ERR_NOT_ENOUGHT_DATA_IN_MATRIX_FILE:
			std::cout << endl << ERR_MSG_NOT_ENOUGHT_DATA_IN_MATRIX_FILE << endl;
			break; 
		case ERR_MATRIX_MULTIPLICATION:
			std::cout << endl << ERR_MSG_MATRIX_MULTIPLICATION << endl;
			break; 
		case ERR_RESULT_ARRAY_TO_FILE:
			std::cout << endl << ERR_MSG_RESULT_ARRAY_TO_FILE << endl;
			break; 
		case ERR_FREE_MATRIX_MEMORY:
			std::cout << endl << ERR_MSG_FREE_MATRIX_MEMORY << endl;
			break;
		default:
			std::cout << endl << "UNEXPECTED ERROR!" << endl;
			break;
	}
	system("pause");
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

//0-Poprawnie zakoñczona funkcja
//ErrorCode - -4 - Niewystarczaj¹ca iloœæ danych w pliku
int matrixFromFileToArray(FILE *file, float **matrix, int rowNumber, int colNumber)
{
	for (int i = 0; i < rowNumber; i++)
	{
		for (int j = 0; j < colNumber; j++)
		{
			if(fscanf(file, "%f", &matrix[i][j]) == EOF) return(-4);
			printf("%.2f ", matrix[i][j]);
		}
		printf("\n");
	}

	return(0);
}

//0 - wszystko posz³o zgodnie z planem - macierz pomno¿ona
//ErrorCode - -3 - Problem z alokacj¹ pamiêci dla macierzy 
//ErrorCode - -5 - Podanych macierzy nie mo¿na pomno¿yæ
int matrixMultiplication(float **firstMatrix, float **secondMatrix, int FMRows, int FMColumns, int SMRows, int SMColumns, float **&resultMatrix, int *RMRows, int *RMColumns)
{
	//Sprawdzenie czy macierze mo¿na mno¿yæ
	if (FMColumns != SMRows) return(-5);

	//Stworzenie wymiarów nowej macierzy
	*RMRows = FMRows;
	*RMColumns = SMColumns;

	//Alokacja pamiêci nowej macierzy
	int state = matrixMemoryAlocation(resultMatrix, *RMRows, *RMColumns);
	if (state != 0) return(state);

	//Przypisanie wartoœci do zaalokowanej tablicy
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

//0 - wszystko posz³o zgodnie z planem - macierz pomno¿ona
//ErrorCode - -6 - Problem z w³o¿eniem danych do pliku
int resultArrayToFile(FILE *outputFile, float **matrix, int rowNumber, int colNumber)
{
	try
	{
		//Wpisanie wymiarów macierzy do pliku
		fprintf(outputFile, "%d ", rowNumber);
		fprintf(outputFile, "%d\n", colNumber);

		//Zapisanie zawartoœæ macierzy
		for (int i = 0; i < rowNumber; i++)
		{
			for (int j = 0; j < colNumber; j++)
			{
				fprintf(outputFile, "%.2f ", matrix[i][j]);
			}
			fprintf(outputFile, "\n");
		}
	}
	catch (const std::exception&)
	{
		return(-6);
	}

	return(0);
}

//0 - wszystko posz³o zgodnie z planem - macierz pomno¿ona
//ErrorCode - -7 - Problem ze zwolnieniem pamiêci
int freeMatrixMemory(float **&matrix, int rowNumber)
{
	try
	{
		for (int i = 0; i < rowNumber; i++)
		{
			free(matrix[i]);
		}
		free(matrix);
	}
	catch (const std::exception&)
	{
		return(-7);
	}
	return(0);
}