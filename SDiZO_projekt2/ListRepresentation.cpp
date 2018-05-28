#include "ListRepresentation.h"



List::List()
{
	list = new BidirectionalListManagement[0];
	vertices = 0;
	edges = 0;
}

List::List(BidirectionalListManagement* list, int vertices, int edges)
{
	this->list = list;
	this->vertices = vertices;
	this->edges = edges;
}


List::~List()
{
	delete[] this->list;
}

void List::addVertex()
{
	this->vertices++;
	BidirectionalListManagement* temp = new BidirectionalListManagement[vertices];

	for (int i = 0; i < vertices - 1; i++)
	{
		temp[i] = list[i];
	}
	BidirectionalListManagement newVertex;
	temp[vertices - 1] = newVertex;

	list = temp;

	delete[]temp;
}

void List::removeVertex(int index)
{
	//first we delete every edge connected to index
	//whether it is directed or indirected graph
	for (int i = 0 ; i < vertices; i++)
	{
		int position = list[i].findElementPos(index);
		if (position >= 0)
		{
			list[i].deleteElement(position);
		}
	}

	//then we rewrite every vertex but the one we want to delete
	this->vertices--;
	
	BidirectionalListManagement* temp = new BidirectionalListManagement[vertices - 1];

	for(int i = 0 ; i < index; i++)
	{
		temp[i] = list[i];
	}

	for (int i = index + 1; i < vertices + 1; i++)
	{
		temp[i - 1] = list[i];
	}


	list = temp;

	delete[] temp;
}

void List::addEdge(int fromVertex, int toVertex, int weight, bool directed)
{
	list[fromVertex].addNewElementEnd(toVertex, weight);
	if (!directed)
	{
		list[toVertex].addNewElementEnd(fromVertex, weight);
	}
}

void List::removeEdge(int fromVertex, int toVertex, bool directed)
{
	list[fromVertex].deleteElement(toVertex);
	if (!directed)
	{
		list[toVertex].deleteElement(fromVertex);
	}
}
