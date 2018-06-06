#include "Graph.h"



Graph::Graph()
{
	this->listRepresentation = List();
	this->matrixRepresentation = Matrix();
	this->directed = false;

	this->timeCounter = TimeCounter();
}

Graph::Graph(bool directed)
{
	this->timeCounter = TimeCounter();
	this->directed = directed;
	this->listRepresentation = List();
	this->matrixRepresentation = Matrix();
}

Graph::Graph(List listRepresentation, Matrix matrixRepresentation, bool directed)
{
	this->timeCounter = TimeCounter();
	//vertices and edges are taken from matrix representation
	this->listRepresentation = listRepresentation;
	this->matrixRepresentation = matrixRepresentation;
	this->directed = directed;
}

Graph::~Graph()
{
}

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
	int v1 = -1, v2 = -1, d = -1;
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

bool Graph::isDirected()
{
	return this->directed;
}

int Graph::getVertices()
{
	return matrixRepresentation.getVertices();
}

void Graph::editEdge(int from, int to, int weight)
{
	listRepresentation.editEdge(from, to, weight);
	matrixRepresentation.editEdge(from, to, weight);
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
		std::cout << "Podaj gestosc grafu w procentach (1-99):";
		std::cin >> den;
		std::cin.get();
	} while (den <= 0 || den >= 100);

	do
	{
		std::cout << "Podaj górny zakres losowania wagi (dolny = 1):";
		std::cin >> weight;
		std::cin.get();
	} while (weight < 1);

	timeCounter.start();
	fillRandom(ver, den, weight);
	std::cout << "Time: " << timeCounter.stop() << " ms." << std::endl;
}

void Graph::fillRandom(int vertices, int density, int weightRange)
{
	double d = static_cast<double>(density) / 100;
	std::cout << "d = " << d << std::endl;
	int edges = 0;

	//it's transformed formula for density of graph
	if (!directed) edges = static_cast<double>(d)*static_cast<double>(vertices)*static_cast<double>(vertices - 1) / 2;
	else edges = static_cast<double>(d)*static_cast<double>(vertices)*static_cast<double>(vertices - 1);
	int fromVertex = 0, toVertex = 0;
	int w = 0;
	int edgesInMatrix = 0;

	listRepresentation = List();
	matrixRepresentation = Matrix(vertices, edges);

	listRepresentation.addVertex();


	for (int i = 1 ;i < vertices; i++)
	{
		//randomize weight
		w = rand() % weightRange + 1;
		//add vertex i
		listRepresentation.addVertex();
		//connect vertex i with previous vertex i - 1
		//to make graph consistent
		listRepresentation.addEdge(i - 1, i, w,directed);
		if (directed)
		{
			matrixRepresentation.setValueOnMatrix(edgesInMatrix, i - 1, -w);
		}
		else
		{
			matrixRepresentation.setValueOnMatrix(edgesInMatrix, i - 1, w);
		}
		matrixRepresentation.setValueOnMatrix(edgesInMatrix, i, w);

		//increment index of edge that will be put next
		edgesInMatrix++;

		if (edgesInMatrix % 100 == 0) std::cout << "DODAWANIE: " << edgesInMatrix << "/" << edges << std::endl;
		edgesInMatrix++;
	}

	//add more edges if needed
	for (int i = 0; i < edges - (vertices - 1); i++)
	{
		if(edgesInMatrix % 100 == 0) std::cout << "DODAWANIE: " << edgesInMatrix << "/" << edges << std::endl;
		edgesInMatrix++;

		//find edge which not exist yet and isn't self edge
		do
		{
			fromVertex = rand() % vertices;
			toVertex = rand() % vertices;
		} while (listRepresentation.doesEdgeExists(fromVertex, toVertex) || fromVertex == toVertex);
		
		//randomize weight
		w = rand() % weightRange + 1;

		//add edge to list
		listRepresentation.addEdge(fromVertex, toVertex, w, directed);

		//add edge to matrix
		if (directed)
		{
			matrixRepresentation.setValueOnMatrix(edgesInMatrix, fromVertex, -w);
		}
		else
		{
			matrixRepresentation.setValueOnMatrix(edgesInMatrix, fromVertex, w);
		}
		matrixRepresentation.setValueOnMatrix(edgesInMatrix, toVertex, w);
		edgesInMatrix++;


		//different method for finding good edge to add
		/*fromVertex = rand() % vertices;
		toVertex = rand() % vertices;

		for(int j = 0; j < vertices; j++)
		{
			for(int k = 0 ; k < vertices; k++)
			{
				if (matrixRepresentation.doesEdgeExist(fromVertex,toVertex) || fromVertex == toVertex)
				{
					if (toVertex == vertices - 1) toVertex = 0;
					else toVertex++;
				}
				else
				{
					break;
				}
			}

			if (matrixRepresentation.doesEdgeExist(fromVertex, toVertex) || fromVertex == toVertex)
			{
				if (fromVertex == vertices - 1) fromVertex = 0;
				else fromVertex++;
			}
			else
			{
				break;
			}
		}*/

		//addEdge(fromVertex,toVertex,rand()%weightRange + 1);
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
	listRepresentation = List();
	matrixRepresentation = Matrix();

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

void Graph::dijkstra()
{
	int to = 0, from = 0;
	do
	{
		std::cout << "Podaj wierzcholek poczatkowy (0 - " << matrixRepresentation.getVertices() - 1 << "): ";
		std::cin >> from;
		std::cin.get();
	} while (from < 0 || from > matrixRepresentation.getVertices() - 1);

	do
	{
		std::cout << "Podaj wierzcholek koncowy (0 - " << matrixRepresentation.getVertices() - 1 << "): ";
		std::cin >> to;
		std::cin.get();
	} while (to < 0 || to > matrixRepresentation.getVertices() - 1);
	dijkstra(from,to);
}

void Graph::dijkstra(int from, int to)
{
	std::cout << "Algorytm Dijkstry:" << std::endl;

	timeCounter.start();
	std::cout << "\tMacierz - dystans:\n" << matrixRepresentation.dijkstra(from, to, directed) << std::endl;
	std::cout << "CZAS: " << timeCounter.stop() << std::endl;

	timeCounter.reset();

	timeCounter.start();
	std::cout << "\tLista - dystans:\n" << listRepresentation.dijkstra(from, to) << std::endl;
	std::cout << "CZAS: " << timeCounter.stop() << std::endl;
}

void Graph::prim()
{
	int from = 0;
	do
	{
		std::cout << "Podaj wierzcholek poczatkowy (0 - " << matrixRepresentation.getVertices() - 1 << "): ";
		std::cin >> from;
		std::cin.get();
	} while (from < 0 || from > matrixRepresentation.getVertices() - 1);

	prim(from);
}

void Graph::prim(int from)
{
	std::cout << "Algorytm Prima:" << std::endl;
	std::cout << "\tMacierz - waga drzewa: " << matrixRepresentation.prim2(from) << std::endl;
	//std::cout << "\tMacierz - algorytm nieefektywny - waga drzewa: " << matrixRepresentation.prim(from) << std::endl;
	std::cout << "\tLista - waga drzewa: " << listRepresentation.prim2(from) << std::endl;
	//std::cout << "\tLista - algorytm nieefektywny - waga drzewa: " << listRepresentation.prim(from) << std::endl;
}

void Graph::test()
{

}
