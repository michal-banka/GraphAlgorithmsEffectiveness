#include "Matrix.h"


Matrix::Matrix()
{
	this->vertex = 0;

	table2d = new int*[vertex];
	for (int i = 0; i < vertex; i++)
	{
		table2d[i] = new int[vertex];
	}
	
}

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
		delete[] this->table2d[i];
	}

	delete [] this->table2d;
}

void Matrix::addNNewVertex()
{
	int n = -1;
	do
	{
		std::cout << "Podaj ilosc nowych krawedzi:\t";
		std::cin >> n;
		std::cin.get();
	} while (n < 0);
	addNNewVertex(n);
}

void Matrix::addNNewVertex(int n)
{
	int newVertex = n + vertex;

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
}

void Matrix::removeVertex()
{
	int n = -1;
	do
	{
		std::cout << "Podaj numer krawedzi do usuniecia:\t";
		std::cin >> n;
		std::cin.get();
	} while (n < 0);

	removeVertex(n);
}

void Matrix::removeVertex(int n)
{
	int newVertex = vertex - 1;
	int** temp = new int*[newVertex];
	for (int i = 0; i < newVertex; i++)
	{
		temp[i] = new int[newVertex];
	}

	for (int i = 0; i < newVertex; i++)
	{
		for (int j = 0; j < newVertex; j++)
		{
			if (j >= n && i < n) temp[i][j] = table2d[i][j + 1];
			else if (j < n && i >= n) temp[i][j] = table2d[i + 1][j];
			else if (j >= n && i >= n) temp[i][j] = table2d[i + 1][j + 1];
			else temp[i][j] = table2d[i][j];
		}
	}

	table2d = temp;
	vertex = newVertex;
}

void Matrix::addEdge()
{
	int v1 = -1, v2 = -1, w = -1;
	do
	{
		std::cout << "Podaj numer poczatkowego wierzcholka (0 - " << vertex << "):\t";
		std::cin >> v1;
		std::cin.get();
	} while (v1 < 0 || v1 > vertex);

	do
	{
		std::cout << "Podaj numer koncowego wierzcholka (0 - " << vertex << "):\t";
		std::cin >> v2;
		std::cin.get();
	} while (v2 < 0 || v2 > vertex);

	do
	{
		std::cout << "Podaj wage krawedzi:\t";
		std::cin >> w;
		std::cin.get();
	} while (w < 0);

	addEdge(v1, v2, w);
}

void Matrix::addEdge(int fromVertex, int toVertex, int weight)
{
	table2d[fromVertex][toVertex] = weight;
	table2d[toVertex][fromVertex] = weight;
}

void Matrix::removeEdge()
{
	int v1 = -1, v2 = -1;
	do
	{
		std::cout << "Podaj numer poczatkowego wierzcholka (0 - " << vertex << "):\t";
		std::cin >> v1;
		std::cin.get();
	} while (v1 < 0 || v1 > vertex);
	
	do
	{
		std::cout << "Podaj numer koncowego wierzcholka (0 - " << vertex << "):\t";
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

void Matrix::showMatrix()
{
	
	for (int i = 0; i < 32; i++)
	{
		std::cout << (char)219;
	}

	std::cout << std::endl << "Macierz [" << vertex << (char)158 << vertex << "] " << std::endl;

	for (int i = 0; i < 32; i++)
	{
		std::cout << (char)176;
	}

	std::cout << std::endl;
	
	for (int i = 0; i < vertex; i++)
	{
		for (int j = 0; j < vertex; j++)
		{
			std::cout << table2d[i][j] << "\t";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	for (int i = 0; i < 32; i++)
	{
		std::cout << (char)219;
	}
	std::cout << std::endl;
}
