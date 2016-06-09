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

#define OK 0
using namespace std;

int main()
{
	//###Czytanie z pliku###
	//###Returned 1 oznacza b³êdne zakoñæzenie programu###
	//###Returned 0 oznacza prawid³owe zakoñczenie programu###

	//Deklaracja plików
	FILE *firstMatrixFile, *secondMatrixFile, *outputFile;

	//Zmienne do danych z plików {FM - FirstMatrix | SM - SecondMatrix}
	int FMRows=0, FMColumns=0, SMRows=0, SMColumns=0;

	//Deklaracja stanu dla sprawdzania errorCodes
	int state;

	//Otwarcie plików 
	state = openFile(firstMatrixFile, "firstMatrixFile.txt", "r");
	if (state != OK) { showError(state); return 1; }
	state = openFile(secondMatrixFile, "secondMatrixFile.txt", "r");
	if (state != OK) { showError(state); return 1; }
	state = openFile(outputFile, "resultMatrix.txt", "w");
	if (state != OK) { showError(state); return 1; }

	//Okreœlenie d³ugoœci wierszy i kolumn
	state = getRowsAndColsSize(firstMatrixFile, secondMatrixFile, &FMRows, &FMColumns, &SMRows, &SMColumns);
	if (state != OK) { showError(state); return 1; }

	//Alokacja pamiêci
	float **firstMatrix = 0, **secondMatrix = 0;

	state = matrixMemoryAlocation(firstMatrix,FMRows,FMColumns);
	if (state != OK) { showError(state); return 1; }
	state = matrixMemoryAlocation(secondMatrix, SMRows, SMColumns);
	if (state != OK) { showError(state); return 1; }

	//Czytanie po ca³ych plikach i zapisanie danych do odpowiednich tablic
	printf("First matrix:\n");
	state = matrixFromFileToArray(firstMatrixFile, firstMatrix, FMRows, FMColumns);
	if (state != OK) { showError(state); return 1; }


	printf("\nSecond matrix:\n");
	state = matrixFromFileToArray(secondMatrixFile, secondMatrix, SMRows, SMColumns);
	if (state != OK) { showError(state); return 1; }

	//MNO¯ENIE
	float **resultMatrix = 0;
	int RMRows = 0, RMColumns = 0;
	printf("\nResult matrix:\n");

	state = matrixMultiplication(firstMatrix, secondMatrix, FMRows, FMColumns, SMRows, SMColumns, resultMatrix, &RMRows, &RMColumns);
	if (state != OK) { showError(state); return 1; }

	//Zapisanie wyniku do pliku
	state = resultArrayToFile(outputFile, resultMatrix, RMRows, RMColumns);
	if (state != OK) { showError(state); return 1; }

	//Zwolnienie pamiêci
	//First matrix
	state = freeMatrixMemory(firstMatrix, FMRows);
	if(state != OK) { showError(state); return 1; }

	//Second matrix
	state = freeMatrixMemory(secondMatrix, SMRows);
	if (state != OK) { showError(state); return 1; }

	//Output matrix
	state = freeMatrixMemory(resultMatrix, RMRows);
	if (state != OK) { showError(state); return 1; }

	//Zamkniêcie plików
	fclose(firstMatrixFile);
	fclose(secondMatrixFile);
	fclose(outputFile);

	system("pause");
    return 0;
}

