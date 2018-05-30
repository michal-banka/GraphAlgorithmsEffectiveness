#include "MatrixRepresentation.h"
#include <complex.h>


Matrix::Matrix()
{
	this->vertices = 0;
	this->edges = 0;

	tab = new int*[edges];
	
}

Matrix::Matrix(int vertices, int edges)
{
	this->vertices = vertices;
	this->edges = edges;

	tab = new int*[edges];
	for (int i = 0; i < edges; i++)
	{
		tab[i] = new int[vertices];
		for(int j = 0; j < vertices; j++)
		{
			tab[i][j] = 0;
		}
	}
}

Matrix::~Matrix()
{
	for (int i = 0; i < edges; i++)
	{
		delete[] this->tab[i];
	}

	delete [] this->tab;
}

int Matrix::getVertices()
{
	return this->vertices;
}

int Matrix::getEdges()
{
	return this->edges;
}

void Matrix::addVertex()
{
	if (edges == 0)
	{
		this->vertices++;
		return;
	}

	//temporary array
	int** temp = new int*[edges];
	for (int i = 0; i < edges; i++)
	{
		temp[i] = new int[vertices + 1];
	}

	for (int i = 0; i < edges; i++)
	{
		for (int j = 0; j < vertices; j++)
		{
			temp[i][j] = tab[i][j];
		}
		temp[i][vertices - 1] = 0;
	}

	this->vertices++;

	tab = temp;
}

void Matrix::removeVertex()
{
	int n = -1;
	do
	{
		std::cout << "Podaj numer wierzcholka do usuniecia (0 - " << vertices << "):\t";
		std::cin >> n;
		std::cin.get();
	} while (n < 0);

	removeVertex(n);
}

void Matrix::removeVertex(int n)
{
	//we have to delete one vertex and every edge that is connected to it
	if (n < 0 || n > vertices)
	{
		std::cout << "Macierz pusta lub zly wybor, nic nie usunieto !" << std::endl;
		return;
	}

	int edgesToDelete = 0;

	for (int i = 0; i < edges; i++)
	{
		//check if that edge is NOT connected to vertex that is being deleted now
		if (tab[i][n] == 0)
		{
			//if not rewrite line but without column n
			for (int j = 0; j < n; j++)
			{
				tab[i - edgesToDelete][j] = tab[i][j];
			}
			for (int j = n + 1; j < vertices; j++)
			{
				tab[i - edgesToDelete][j] = tab[i][j];
			}
		}
		else
		{
			edgesToDelete++;
		}
	}

	//vertex has been removed and every cells in tab were moved up left
	//so now we just cut not needed anymore lines and columns

	int** temp = new int*[edges - edgesToDelete];
	for (int i = 0; i < edges - edgesToDelete; i++)
	{
		temp[i] = new int[vertices - 1];
	}

	this->vertices--;
	this->edges -= edgesToDelete;

	for (int i = 0 ; i < edges; i++)
	{
		for (int j = 0; j < vertices; j++)
		{
			temp[i][j] = tab[i][j];
		}
	}

	tab = temp;
}

void Matrix::addEdge()
{
	int v1 = -1, v2 = -1, w = -1, d = -1;
	do
	{
		std::cout << "Podaj numer poczatkowego wierzcholka (0 - " << vertices - 1<< "):\t";
		std::cin >> v1;
		std::cin.get();
	} while (v1 < 0 || v1 > vertices);

	do
	{
		std::cout << "Podaj numer koncowego wierzcholka (0 - " << vertices - 1 << "):\t";
		std::cin >> v2;
		std::cin.get();
	} while (v2 < 0 || v2 > vertices);

	do
	{
		std::cout << "Podaj wage krawedzi:\t";
		std::cin >> w;
		std::cin.get();
	} while (w < 0);

	do
	{
		std::cout << "Krawedz skierowana? \n1. Tak \n2. Nie \nTwoj wybor:";
		std::cin >> d;
		std::cin.get();
	} while (d < 1 || d > 2);


	if (d == 1) addEdge(v1, v2, w, true);
	else addEdge(v1, v2, w, false);
}

void Matrix::addEdge(int fromVertex, int toVertex, int weight, bool directed)
{
	this->edges++;

	int** temp = new int*[edges];
	for (int i = 0; i < edges; i++)
	{
		temp[i] = new int[vertices];
	}

	//rewrite tab to temp
	for (int i = 0; i < edges - 1; i++)
	{
		for (int j = 0; j < vertices; j++)
		{
			temp[i][j] = tab[i][j];
		}
	}

	//fill new edge with 0
	for (int i = 0; i < vertices; i++)
	{
		temp[edges - 1][i] = 0;
	}

	//put two weigths on last line (new edge)
	if (directed)
	{
		temp[edges - 1][fromVertex] = -weight;
	}
	else
	{
		temp[edges - 1][fromVertex] = weight;
	}
	temp[edges - 1][toVertex] = weight;

	tab = temp;
}

void Matrix::removeEdge()
{
	int v1 = -1, v2 = -1, w = -1, d = -1;
	do
	{
		std::cout << "Podaj numer poczatkowego wierzcholka (0 - " << vertices - 1 << "):\t";
		std::cin >> v1;
		std::cin.get();
	} while (v1 < 0 || v1 > vertices);

	do
	{
		std::cout << "Podaj numer koncowego wierzcholka (0 - " << vertices - 1 << "):\t";
		std::cin >> v2;
		std::cin.get();
	} while (v2 < 0 || v2 > vertices);

	do
	{
		std::cout << "Krawedz skierowana? \n1. Tak \n2. Nie \nTwoj wybor:";
		std::cin >> d;
		std::cin.get();
	} while (d < 1 || d > 2);

	if (d == 1) removeEdge(v1, v2, true);
	else removeEdge(v1, v2, false);
}

void Matrix::removeEdge(int fromVertex, int toVertex, bool directed)
{
	if (edges == 0 || fromVertex > vertices - 1 || fromVertex < 0 || toVertex < 0 || toVertex > vertices - 1) return;

	//check if this edge exists
	for (int i = 0 ; i < edges; i++)
	{
		//if yes rewrite tab without this one edge
		if (tab[i][fromVertex] != 0 && tab[i][toVertex] != 0)
		{
			this->edges--;

			int** temp = new int*[edges];
			for (int i = 0; i < edges; i++)
			{
				temp[i] = new int[vertices];
			}

			for (int j = 0; j < i; j++)
			{
				temp[j] = tab[j];
			}

			for (int j = i + 1;j < edges; j++)
			{
				temp[j - 1] = tab[j];
			}
			tab = temp;
			return;
		}
	}

	std::cout << "Nie znaleziono takiej krawêdzi" << std::endl;
}

void Matrix::show()
{
	
	for (int i = 0; i < 32; i++)
	{
		std::cout << (char)219;
	}

	std::cout << std::endl << "Reprezentacja macierzowa\n [" << edges << (char)158 << vertices << "] " << std::endl;

	for (int i = 0; i < 32; i++)
	{
		std::cout << (char)176;
	}

	std::cout << std::endl;
	
	for (int i = 0; i < edges; i++)
	{
		for (int j = 0; j < vertices; j++)
		{
			std::cout << tab[i][j] << "\t";
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
