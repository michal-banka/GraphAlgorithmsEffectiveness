#include "Matrix.h"


Matrix::Matrix(int vertex)
{
	this->vertex = vertex;

	table2d = new int*[vertex];
	for (int i = 0; i < vertex; i++)
	{
		table2d[i] = new int[vertex];
	}
}

Matrix::~Matrix()
{
	for (int i = 0; i < vertex; i++)
	{
		delete[] table2d[i];
	}

	delete[] *table2d;
}

void Matrix::addNNewVertex(int NNewVertex)
{
	int newVertex = NNewVertex + vertex;


	int** temp = new int*[newVertex];
	for (int i = 0; i < newVertex; i++)
	{
		temp[i] = new int[newVertex];
	}

	//rewrite all existing rows
	for (int i = 0; i < vertex; i++)
	{
		//and columns
		for (int j = 0; j < vertex; j++)
		{
			temp[i][j] = table2d[i][j];
		}
		//add new column cell to new columns
		for (int j = vertex; j < newVertex; j++)
		{
			temp[i][j] = 0;
		}
	}
	//add new rows
	for (int i = vertex; i < newVertex; i++)
	{
		for (int j = 0; j < newVertex; j++)
		{
			temp[i][j] = 0;
		}
	}

	table2d = temp;
	vertex = newVertex;
	

	for (int i = 0; i < newVertex; i++)
	{
		delete[] temp[i];
	}

	delete[] * temp;

}

void Matrix::insertEdge()
{
	int v1 = -1, v2 = -1, w = -1;
	do
	{
		std::cout << "Podaj numer poczatkowego wierzcholka (0 - " << v1 << "):\t";
		std::cin >> v1;
		std::cin.get();
	} while (v1 < 0 || v1 > vertex);

	do
	{
		std::cout << "Podaj numer koncowego wierzcholka (0 - " << v2 << "):\t";
		std::cin >> v2;
		std::cin.get();
	} while (v2 < 0 || v2 > vertex);

	do
	{
		std::cout << "Podaj wage krawedzi):\t";
		std::cin >> v2;
		std::cin.get();
	} while (w < 0);

	insertEdge(v1, v2, w);
}

void Matrix::insertEdge(int fromVertex, int toVertex, int weight)
{
	table2d[fromVertex][toVertex] = weight;
	table2d[toVertex][fromVertex] = weight;
}

void Matrix::removeEdge()
{
	int v1 = -1, v2 = -1;
	do
	{
		std::cout << "Podaj numer poczatkowego wierzcholka (0 - " << v1 << "):\t";
		std::cin >> v1;
		std::cin.get();
	} while (v1 < 0 || v1 > vertex);

	do
	{
		std::cout << "Podaj numer koncowego wierzcholka (0 - " << v2 << "):\t";
		std::cin >> v2;
		std::cin.get();
	} while (v2 < 0 || v2 > vertex);
	removeEdge(v1, v2);
}

void Matrix::removeEdge(int fromVertex, int toVertex)
{
	table2d[fromVertex][toVertex] = 0;
	table2d[toVertex][fromVertex] = 0;
}
