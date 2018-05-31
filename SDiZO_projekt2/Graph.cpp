#include "Graph.h"



Graph::Graph()
{
	this->listRepresentation = List();
	this->matrixRepresentation = Matrix();
	this->directed = false;
}

Graph::Graph(bool directed)
{
	this->directed = directed;
	this->listRepresentation = List();
	this->matrixRepresentation = Matrix();
}

Graph::Graph(List listRepresentation, Matrix matrixRepresentation, bool directed)
{
	//vertices and edges are taken from matrix representation
	this->listRepresentation = listRepresentation;
	this->matrixRepresentation = matrixRepresentation;
	this->directed = directed;
}

Graph::~Graph(){}

void Graph::addVertex()
{
	listRepresentation.addVertex();
	matrixRepresentation.addVertex();
}

void Graph::removeVertex()
{
	int n = -1;
	do
	{
		std::cout << "Podaj numer wierzcholka do usuniecia (0 - " << matrixRepresentation.getVertices() <<  "): ";
		std::cin >> n;
		std::cin.get();
	} while (n < 0 || n > matrixRepresentation.getEdges());

	removeVertex(n);
}

void Graph::removeVertex(int n)
{
	listRepresentation.removeVertex(n);
	matrixRepresentation.removeVertex(n);
}

void Graph::addEdge()
{
	int v1 = -1, v2 = -1, w = -1, d = -1;
	do
	{
		std::cout << "Podaj numer poczatkowego wierzcholka (0 - " << matrixRepresentation.getVertices() - 1 << "):\t";
		std::cin >> v1;
		std::cin.get();
	} while (v1 < 0 || v1 > matrixRepresentation.getVertices());

	do
	{
		std::cout << "Podaj numer koncowego wierzcholka (0 - " << matrixRepresentation.getVertices() - 1 << "):\t";
		std::cin >> v2;
		std::cin.get();
	} while (v2 < 0 || v2 > matrixRepresentation.getVertices());

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


	if (d == 1) addEdge(v1, v2, w);
	else addEdge(v1, v2, w);
}

void Graph::addEdge(int fromVertex, int toVertex, int weight)
{
	listRepresentation.addEdge(fromVertex, toVertex, weight, directed);
	matrixRepresentation.addEdge(fromVertex, toVertex, weight, directed);
}


void Graph::removeEdge()
{
	int v1 = -1, v2 = -1, w = -1, d = -1;
	do
	{
		std::cout << "Podaj numer poczatkowego wierzcholka (0 - " << matrixRepresentation.getEdges() - 1 << "):\t";
		std::cin >> v1;
		std::cin.get();
	} while (v1 < 0 || v1 > matrixRepresentation.getEdges());

	do
	{
		std::cout << "Podaj numer koncowego wierzcholka (0 - " << matrixRepresentation.getEdges() - 1 << "):\t";
		std::cin >> v2;
		std::cin.get();
	} while (v2 < 0 || v2 > matrixRepresentation.getEdges());

	do
	{
		std::cout << "Krawedz skierowana? \n1. Tak \n2. Nie \nTwoj wybor:";
		std::cin >> d;
		std::cin.get();
	} while (d < 1 || d > 2);

	if (d == 1) removeEdge(v1, v2);
	else removeEdge(v1, v2);
}

void Graph::removeEdge(int fromVertex, int toVertex)
{
	listRepresentation.removeEdge(fromVertex, toVertex, directed);
	matrixRepresentation.removeEdge(fromVertex, toVertex, directed);
}


void Graph::showRepresentations()
{
	listRepresentation.show();
	std::cout << std::endl;
	matrixRepresentation.show();
}

void Graph::fillRandom()
{
	int ver = -1, den = -1, weight = -1;
	do
	{
		std::cout << "Podaj ilosc wierzcholkow:";
		std::cin >> ver;
		std::cin.get();
	} while (ver <= 0);

	do
	{
		std::cout << "Podaj gestosc grafu w procentach (0-100):";
		std::cin >> den;
		std::cin.get();
	} while (den < 0 || den > 100);

	do
	{
		std::cout << "Podaj górny zakres losowania wagi (dolny = 1):";
		std::cin >> weight;
		std::cin.get();
	} while (weight < 1);

	fillRandom(ver, den, weight);
}

void Graph::fillRandom(int vertices, int density, int weightRange)
{
	int edges = (double) density / 100 * vertices;
	int fromVertex = 0, toVertex = 0;

	for (int i = 0 ;i < vertices; i++)
	{
		addVertex();
	}

	for (int i = 0 ; i < edges; i++)
	{
		//rand edge
		//it's (vertices-1)! possible edges (when directed)
		//so when we put not more than verticles edges
		//chance for long randomizing is very low
		do
		{
			fromVertex = rand() % vertices;
			toVertex = rand() % vertices;
		} while (listRepresentation.doesEdgeExists(fromVertex, toVertex) || fromVertex == toVertex);

		int k = 0;

		//not the best method
		/*for (int i = 0; i < vertices; i++)
		{
			for (int j = 0; j < vertices; j++)
			{
				std::cout << k++ << std::endl;
				if (listRepresentation.doesEdgeExists(fromVertex, toVertex)) //|| toVertex == fromVertex)
				{
					toVertex = (toVertex + 1) % vertices;
				}
				else
				{
					break;
				}
			}
			fromVertex = (fromVertex + 1) % vertices;
		};*/

		addEdge(fromVertex,toVertex,rand()%weightRange + 1);
	}
}

void Graph::fillFromFile()
{
	std::string filename = "";
	do
	{
		std::cout << "Podaj nazwe pliku wraz z rozszerzeniem: ";
		std::cin >> filename;
		std::cin.get();
	} while (filename.length() <= 0);
	fillFromFile(filename);
}

void Graph::fillFromFile(std::string filename)
{
	//txt file must have specific format
	//as mentioned in project documentation
	int vertices = 0;
	int toVertex = 0, fromVertex = 0, weight = 0;
	
	std::ifstream read;
	read.open(filename);
	if (read.is_open())
	{
		//first line is always in file
		//[number of edges] [number of vertices]
		//I will use only number of vertices
		read >> vertices;
		read >> vertices;
		

		for (int i = 0 ; i < vertices; i++) addVertex();

		while(!read.eof())
		{
			read >> fromVertex;
			read >> toVertex;
			read >> weight;

			addEdge(fromVertex, toVertex, weight);
		}
	}
	else
	{
		std::cout << "Blad odczytu pliku" + filename << std::endl;
	}

	read.close();
}
