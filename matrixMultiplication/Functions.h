#pragma once

//0 - podanych macierzy nie mo¿na pomno¿yæ
//1 - wszystko posz³o zgodnie z planem - macierz pomno¿ona
//RM - ResultMatrix
int matrixMultiplication(float **firstMatrix, float **secondMatrix, int FMRows, int FMColumns, int SMRows, int SMColumns, float **&resultMatrix, int *RMRows, int *RMColumns)
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