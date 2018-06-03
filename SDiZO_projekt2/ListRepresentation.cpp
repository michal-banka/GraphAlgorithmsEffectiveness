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
	/*for(int i = 0; i < vertices; i++)
	{
		delete list[i].getHead();
	}*/
	//delete[] this->list;
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
		std::cout << "Podaj wage krawedzi (1 - 999):\t";
		std::cin >> w;
		std::cin.get();
	} while (w <= 0 || w >= 1000);

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
	int v1 = -1, v2 = -1, d = -1;
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

int List::dijkstra()
{
	int v1 = -1, v2 = -1;
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

	return dijkstra(v1, v2);
}

int List::dijkstra(int from, int to)
{
	if (vertices <= 0 || from < 0 || to < 0 || from > vertices -1 || to > vertices - 1) return -1;

	//create struct which will represent road to any vertex
	struct dijkstraNode
	{
		int distance = 0;
		int previous = -1;
	};

	//construct list to inform which vertex were checked, 
	//it could be simple array but I don't use STL becouse of requirements of project and list is already implemented
	//what is more, list has better times of adding to end
	//constructor fullfil list with 0 as value
	//0 - not checked, 1 - checked
	BidirectionalListManagement checked = BidirectionalListManagement(vertices);
	int now = from;
	dijkstraNode* nodes = new dijkstraNode[vertices];
	//fill every node with distance = 1000 (it's over limit of weight that might be given by user)
	//except nodes[from], it has distance = 0
	
	for(int i = 0 ;i < vertices; i++)
	{
		nodes[i].distance = 1000;
	}

	nodes[from].distance = 0;
	nodes[from].previous = 0;

	//now we check every vertex
	while(checked.doesValueExist(0))
	{
		BidirectionalList* temp = list[now].getHead();

		//check every edge of vertex
		while(temp)
		{
			//if new path is shorter than previous change with new
			if (nodes[now].distance + temp->getWeight() < nodes[temp->getValue()].distance)
			{
				nodes[temp->getValue()].distance = nodes[now].distance + temp->getWeight();
				nodes[temp->getValue()].previous = now;
			}
			temp = temp->getNext();
		}
		checked[now]->setValue(1);
		delete temp;

		//find node with the smallest node distance which has NOT been checked yet
		int min = 1000;

		for (int i = 0 ;i < vertices; i++)
		{
			if (nodes[i].distance < min && checked[i]->getValue() != 1)
			{
				min = nodes[i].distance;
				now = i;
			}
		}
	}

	if (nodes[to].previous == -1)
	{
		std::cout << "Wierzcholek nie polaczony z wierzcholkiem poczatkowym." << std::endl;
		return -1;
	}
	else
	{
		now = to;
		std::cout << "DROGA: ";
		while(now != from)
		{
			std::cout << now << ", ";
			now = nodes[now].previous;
		}
		std::cout << from << std::endl;
		std::cout << "DYSTANS: " << nodes[to].distance << std::endl;
		return nodes[to].distance;
	}
}

int List::prim(int from)
{
	struct node
	{
		int from = -1;
		int to = -1;
		int weight = 0;
	};
	//index of vertex from which we start making tree
	int now = from;
	//size of node array
	int size = 0;
	//size of tree array
	int treeSize = 0;
	
	int idxNode = 0;
	int cycle = false;

	node* tree = new node[treeSize];
	node* nodes = new node[size];
	node* tempNodes = new node[size + list[now].getCount()];


	BidirectionalList* temp = list[now].getHead();

	while (size > 0 || treeSize == 0)
	{
		//delete[] tempNodes;
		temp = list[now].getHead();
		bool inserted = false;
		
		//inserting new node
		while (temp)
		{

			inserted = false;
			int j = 0;

			tempNodes = new node[size + list[now].getCount()];
			//add new edges
			for(int i = 0 ; i < size; i++)
			{
				if (nodes[i].weight > temp->getWeight() && !inserted)
				{
					tempNodes[i + 1] = { nodes[i].from, nodes[i].to, nodes[i].weight };
					tempNodes[i] = { now, temp->getValue(), temp->getWeight() };
					inserted = true;
				}
				else if (!inserted)
				{
					tempNodes[i] = { nodes[i].from, nodes[i].to, nodes[i].weight };
				}
				else
				{
					tempNodes[i + 1] = { nodes[i].from, nodes[i].to, nodes[i].weight };
				}
			}
			if (!inserted)
			{
				tempNodes[size] = { now, temp->getValue(), temp->getWeight() };
				inserted = true;
			}

			size++;
			temp = temp->getNext();

			nodes = tempNodes;
		}
		
		// set next node to check
		idxNode = -1;
		cycle = false;

		for (int i = 0; i < size; i++)
		{
			cycle = false;
			for (int j = 0; j < treeSize; j++)
			{
				if (tree[j].from == nodes[i].to)
				{
					cycle = true;
					break;
				}
			}

			if (!cycle)
			{
				idxNode = i;
				break;
			}
		}
		now = nodes[idxNode].to;
		
		//add node to tree
		node* tempTree = new node[treeSize + 1];
		
		for (int i = 0; i < treeSize; i++)
		{
			tempTree[i] = tree[i];
		}
		tempTree[treeSize] = nodes[idxNode];
		
		treeSize++;
		tree = tempTree;

		//delete nodes from 0 to idxNode
		size = size - idxNode - 1;
		node* tempN = new node[size];
		for (int i = 0; i < size; i++)
		{
			tempN[i] = nodes[i + idxNode + 1];
		}
		nodes = tempN;

		//if all vertices are on tree finish
		if (treeSize == vertices - 1) break;
	};


	//show tree
	std::cout << "Drzewo - Lista: " << std::endl;
	int weight = 0;
	for(int i = 0; i < treeSize; i++)
	{
		std::cout << tree[i].from << " -> " << tree[i].to << " [" << tree[i].weight << "]" << std::endl;
		weight += tree[i].weight;
	}

	delete[] tree;
	delete[] nodes;
	delete[] tempNodes;
	delete temp;

	return weight;
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
