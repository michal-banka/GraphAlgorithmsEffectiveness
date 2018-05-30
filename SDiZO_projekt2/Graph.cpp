#include "Graph.h"



Graph::Graph()
{
	this->listRepresentation = List();
	this->matrixRepresentation = Matrix();
	this->vertices = 0;
	this->edges = 0;
}

Graph::Graph(List listRepresentation, Matrix matrixRepresentation)
{
	//vertices and edges are taken from matrix representation
	this->listRepresentation = listRepresentation;
	this->matrixRepresentation = matrixRepresentation;
	this->vertices = matrixRepresentation.getVertices();
	this->edges = matrixRepresentation.getEdges();
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
	} while (v1 < 0 || v1 > vertices);

	do
	{
		std::cout << "Podaj numer koncowego wierzcholka (0 - " << matrixRepresentation.getVertices() - 1 << "):\t";
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

void Graph::addEdge(int fromVertex, int toVertex, int weight, bool directed)
{
	listRepresentation.addEdge(fromVertex, toVertex, weight, directed);
	matrixRepresentation.addEdge(fromVertex, toVertex, weight, directed);
}

void Graph::removeEdge()
{

}

void Graph::showRepresentations()
{
	listRepresentation.show();
	std::cout << std::endl;
	matrixRepresentation.show();
}
