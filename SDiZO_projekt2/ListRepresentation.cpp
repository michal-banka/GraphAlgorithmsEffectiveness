#include "ListRepresentation.h"



List::List()
{
	this->list = new BidirectionalListManagement[0];
	this->vertices = 0;
}

List::List(BidirectionalListManagement* list, int vertices)
{
	this->list = list;
	this->vertices = vertices;
}

List::~List()
{
	delete[] this->list;
}

int List::getVertices()
{
	return this->vertices;
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
}

void List::removeVertex()
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

void List::removeVertex(int index)
{
	if (index < 0 || index > vertices - 1 || vertices <= 0) return;

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

	//nex decrement value (toVertex index) of every edge that was connected to vertex[index + i]
	//that's becouse while deleting vertex every higher vertex will have new index, which will be prevoius - 1
	for (int i = 0; i < vertices; i++)
	{
		BidirectionalList* temp = list[i].getHead();
		while (temp)
		{
			if (temp->getValue() > index)
			{
				temp->setValue(temp->getValue() - 1);
			}
			temp = temp->getNext();
		}
	}

	//then we rewrite every vertex but the one we want to delete
	this->vertices--;
	
	BidirectionalListManagement* temp = new BidirectionalListManagement[vertices];

	for(int i = 0 ; i < index; i++)
	{
		temp[i] = list[i];
	}

	for (int i = index + 1; i < vertices + 1; i++)
	{
		temp[i - 1] = list[i];
	}


	list = temp;
}

void List::addEdge()
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

void List::addEdge(int fromVertex, int toVertex, int weight, bool directed)
{
	//return if:
	//weight < 0
	//less than 2 vertices
	//any index of vertex doesn't exist
	//this edge already exists

	if (fromVertex < 0 || fromVertex > vertices - 1 || toVertex < 0 ||
		toVertex > vertices - 1 || vertices <= 1 || weight <= 0 || list[fromVertex].findElementPos(toVertex) != -1 ||
		toVertex == fromVertex) return;
	
	list[fromVertex].addNewElementEnd(toVertex, weight);
	if (!directed && fromVertex != toVertex)
	{
		list[toVertex].addNewElementEnd(fromVertex, weight);
	}
}

void List::removeEdge()
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

void List::removeEdge(int fromVertex, int toVertex, bool directed)
{
	if (fromVertex < 0 || fromVertex > vertices - 1 || toVertex < 0 || toVertex > vertices - 1 || vertices <= 0) return;

	list[fromVertex].deleteElement(list[fromVertex].findElementPos(toVertex));

	if (!directed && fromVertex != toVertex)
	{
		list[toVertex].deleteElement(list[toVertex].findElementPos(fromVertex));
	}
}

bool List::doesEdgeExists(int fromVertex, int toVertex)
{
	//O(E)
	return list[fromVertex].findElementPos(toVertex) >= 0;
}

void List::show()
{
	for (int i = 0; i < 32; i++)
	{
		std::cout << (char)219;
	}

	std::cout << std::endl << "Reprezentacja listowa" << std::endl;

	for (int i = 0; i < 32; i++)
	{
		std::cout << (char)176;
	}

	std::cout << std::endl;

	for (int i = 0 ;i < vertices; i++)
	{
		BidirectionalList* element = list[i].getHead();

		std::cout << "[" << i << "]\t:\t";
		while (element)
		{
			std::cout << element->getValue() << " [" << element->getWeight() << "]";
			if (element->getNext())
			{
				std::cout << ",\t";
			}
			element = element->getNext();
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
