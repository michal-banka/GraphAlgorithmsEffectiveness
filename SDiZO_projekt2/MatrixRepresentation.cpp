#include "MatrixRepresentation.h"
#include "BidirectionalListManagment.h"
#include "BinaryHeap.h"


Matrix::Matrix()
{
	this->vertices = 0;
	this->edges = 0;

	this->tab = nullptr;
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

Matrix::Matrix(int** tab, int vertices, int edges)
{
	this->tab = tab;
	this->vertices = vertices;
	this->edges = edges;
}

Matrix::Matrix(const Matrix& m)
{
	this->edges = m.edges;
	this->vertices = m.vertices;

	this->tab = new int*[edges];
	for (int i = 0; i < edges; i++)
	{
		this->tab[i] = new int[vertices];
	}

	for (int i = 0; i < edges; i++)
	{
		for (int j = 0; j < vertices; j++)
		{
			this->tab[i][j] = m.tab[i][j];
		}
	}

}

Matrix::~Matrix()
{
	for(int i = 0 ; i < edges; i++)
	{
		delete[] tab[i];
	}	
	delete[] tab;

}

int Matrix::getVertices()
{
	return this->vertices;
}

int Matrix::getEdges()
{
	return this->edges;
}

void Matrix::setTab(int** tab)
{
	this->tab = tab;
}

void Matrix::setEdges(int edges)
{
	this->edges = edges;
}

void Matrix::setVertices(int vertices)
{
	this->vertices = vertices;
}

void Matrix::setValueOnMatrix(int edge, int vertex, int value)
{
	if (edge <= edges - 1 && vertex <= vertices - 1 && edge >= 0 && vertex >= 0)
	{
		tab[edge][vertex] = value;
	}
}

int Matrix::numberOfEdgesOf(int vertex)
{
	int sum = 0;
	for (int i = 0; i < edges; i++)
	{
		if (tab[i][vertex] != 0) sum++;
	}

	return sum;
}

bool Matrix::doesEdgeExist(int from, int to)
{
	for(int i = 0 ; i < edges; i++)
	{
		if (tab[i][from] != 0 && tab[i][to] > 0) return true;
	}
	return false;
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

	//rewrite old array
	for (int i = 0; i < edges; i++)
	{
		for (int j = 0; j < vertices; j++)
		{
			temp[i][j] = tab[i][j];
		}
		//and add vertice
		temp[i][vertices] = 0;
	}

	this->vertices++;


	for (int i = 0; i < edges; i++)
	{
		delete[] tab[i];
	}
	delete[] tab;

	tab = temp;
}

void Matrix::removeVertex()
{
	if (vertices <= 0) return;
	int n = -1;
	do
	{
		std::cout << "Podaj numer wierzcholka do usuniecia (0 - " << vertices - 1 << "):\t";
		std::cin >> n;
		std::cin.get();
	} while (n < 0);

	removeVertex(n);
}

void Matrix::removeVertex(int n)
{
	//we have to delete one vertex and every edge that is connected to it
	if (n < 0 || n > vertices || vertices <= 0) return;

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

	for (int i = 0; i < edges; i++)
	{
		delete[] tab[i];
	}
	delete[] tab;

	tab = temp;

}

void Matrix::editEdge(int from, int to, int newWeight)
{
	for(int i = 0 ;i < edges; i++)
	{
		if (tab[i][from] != 0 && tab[i][to] != 0)
		{
			if (tab[i][from] < 0) tab[i][from] = -newWeight;
			else tab[i][from] = newWeight;

			if (tab[i][to] < 0) tab[i][to] = -newWeight;
			else tab[i][to] = to;

			return;
		}
	}

	std::cout << "Nie ma takiej krawedzi." << std::endl;
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
		std::cout << "Podaj wage krawedzi (1 - 999):\t";
		std::cin >> w;
		std::cin.get();
	} while (w < 1 || w > 999);

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
	//return if:
		//weight < 0
		//less than 2 vertices
		//any index of vertex doesn't exist
		//this edge already exists
	if (fromVertex > vertices - 1 || fromVertex < 0 || toVertex < 0 || toVertex > vertices || weight <= 0 || vertices <= 1 || fromVertex == toVertex) return;

	this->edges++;

	int** temp = new int*[edges];
	//O(E)
	for (int i = 0; i < edges - 1; i++)
	{
		temp[i] = new int[vertices];

		for (int j = 0; j < vertices; j++)
		{
			temp[i][j] = tab[i][j];
		}
	}
	temp[edges - 1] = new int[vertices];

	//rewrite tab to temp -> new version: rewrite while alocating memory, one loop less
	/*for (int i = 0; i < edges - 1; i++)
	{
		for (int j = 0; j < vertices; j++)
		{
			temp[i][j] = tab[i][j];
		}
	}*/

	//fill new edge with 0
	//O(V)
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

	for (int i = 0; i < edges - 1; i++)
	{
		delete[] tab[i];
	}
	delete[] tab;

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
	if (edges <= 0 || fromVertex > vertices - 1 || fromVertex < 0 || toVertex < 0 || toVertex > vertices - 1) return;

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

			for (int i = 0; i < edges; i++)
			{
				delete[] tab[i];
			}
			delete[] tab;

			tab = temp;

			return;
		}
	}

	std::cout << "Nie znaleziono takiej krawedzi" << std::endl;
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

int Matrix::dijkstra(int from, int to, bool directed)
{
	struct dijkstraNode
	{
		int distance = 0;
		int previous = -1;
	};

	BidirectionalListManagement checked = BidirectionalListManagement(vertices);
	int now = from;
	dijkstraNode* nodes = new dijkstraNode[vertices];

	for (int i = 0; i < vertices; i++)
	{
		nodes[i].distance = 1000;
	}

	nodes[from].distance = 0;
	nodes[from].previous = 0;

	//now we check every vertex
	while (checked.doesValueExist(0))
	{
		//checked.showList();
		for(int i = 0 ;i < edges; i++)
		{
			//first find edge connected to given fromVertex
			if (tab[i][now] < 0 && directed || tab[i][now] != 0 && !directed)
			{
				//when found, find index of toVertex
				for (int j = 0; j < vertices; j++)
				{
					//when found
					//if new path is shorter than previous change with new
					//since when abs doesn't work for ints???
					if (tab[i][j] != 0 && j != now && nodes[now].distance + abs(static_cast<double>(tab[i][now])) < nodes[j].distance)
					{
						nodes[j].distance = nodes[now].distance + abs(static_cast<double>(tab[i][now]));
						nodes[j].previous = now;
						break;
					}
				}
			}
			checked[now]->setValue(1);
		}


		//find node with the smallest node distance which has NOT been checked yet
		int min = 1000;

		for (int i = 0; i < vertices; i++)
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
		delete[] nodes;
		return -1;
	}
	else
	{
		int dist = nodes[to].distance;
		now = to;
		//std::cout << "Droga: ";
		while (now != from)
		{
			//std::cout << now << ", ";
			now = nodes[now].previous;
		}
		//std::cout << from << std::endl;
		delete[] nodes;
		return dist;
	}
}

int Matrix::prim(int from)
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
	node* tempNodes = new node[size + numberOfEdgesOf(now)];

	while (size > 0 || treeSize == 0)
	{
		bool inserted = false;

		//inserting new edge
		for (int i = 0; i < edges; i++)
		{
			//when edge found
			if (tab[i][now] != 0)
			{
				inserted = false;
				tempNodes = new node[size + numberOfEdgesOf(now)];

				//add new edges to nodes array
				for (int j = 0; j < size; j++)
				{
					if (nodes[j].weight > abs(tab[i][now]) && !inserted)
					{
						//find the other end of edge
						for(int k = 0 ;k < vertices; k++)
						{
							//and add to nodes array
							if (tab[i][k] != 0 && k != now)
							{
								tempNodes[j + 1] = { nodes[j].from, nodes[j].to, nodes[j].weight };
								tempNodes[j] = { now, k,  abs(tab[i][now])};
								inserted = true;
							}
						}

						
					}
					else if (!inserted)
					{
						tempNodes[j] = { nodes[j].from, nodes[j].to, nodes[j].weight };
					}
					else
					{
						tempNodes[j + 1] = { nodes[j].from, nodes[j].to, nodes[j].weight };
					}
				}
				if (!inserted)
				{
					//find the other end of edge
					for (int k = 0; k < vertices; k++)
					{
						//and add to nodes array
						if (tab[i][k] != 0 && k != now)
						{
							tempNodes[size] = { now, k,  abs(tab[i][now]) };
							inserted = true;
						}
					}
				}
				size++;
				nodes = tempNodes;
			}
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
	int weight = 0;
	for (int i = 0; i < treeSize; i++)
	{
		std::cout << tree[i].from << " -> " << tree[i].to << " [" << tree[i].weight << "]" << std::endl;
		weight += tree[i].weight;
	}

	delete[] tree;
	delete[] nodes;
	delete[] tempNodes;

	return weight;
}

int Matrix::prim2(int from)
{
	BidirectionalListManagement checked = BidirectionalListManagement(vertices);
	struct primVertex
	{
		int key = 0;
		int previous = -1;
	};

	int now = from;

	primVertex* verticesPrim = new primVertex[vertices];

	for (int i = 0; i < vertices; i++)
	{
		verticesPrim[i] = { 1000, -1 };
	}

	verticesPrim[from] = { 0, from };

	//check all vertices
	while (checked.doesValueExist(0))
	{
		//check all edges of vertice now
		for (int i = 0; i < edges; i++)
		{
			if (tab[i][now] != 0)
			{
				//find the other end of this edge
				int end = 0;
				for (int j = 0; j < vertices; j++)
				{
					if (tab[i][j] != 0 && j != now)
					{
						end = j;
						break;
					}
				}

				//if key of vertice is bigger than weight of edge (now, temp->value()) set key
				if (verticesPrim[end].key > abs(tab[i][end]) && checked[end]->getValue() != 1)
				{
					verticesPrim[end] = { abs(tab[i][end]), now };
				}
				checked[now]->setValue(1);
			}
		}

		//set new now
		int min = 1000;

		for (int i = 0; i < vertices; i++)
		{
			if (verticesPrim[i].key < min && checked[i]->getValue() == 0)
			{
				min = verticesPrim[i].key;
				now = i;
			}
		}
	}

	int dist = 0;
	for (int i = 0; i < vertices; i++)
	{
		if (i != from)
		{
			dist += verticesPrim[i].key;
			//std::cout << verticesPrim[i].previous << " -> " << i << " [" << verticesPrim[i].key << "]" << std::endl;
		}
	}

	delete[] verticesPrim;

	return dist;
}

int Matrix::kruskal()
{
	struct kruskalEdge
	{
		int from = -1;
		int to = -1;
		int weight = 0;
	};

	//create list of incostintent trees made out of unconected vertices
	BidirectionalListManagement checked = BidirectionalListManagement();
	//create array of all edges
	//array must be sorted
	//type of sorting will be heapsort with heap implementation from prevoius project

	//heap will be simple priority queue, we will need only first element to be correct
	//so heap is fine for that
	//and it has O(nlogn) of adding new elem, so really fast
	BinaryHeap priorityQueue = BinaryHeap();
	for (int i = 0; i< vertices; i++)
	{
		checked.addNewElementEnd(i, 0);

		//while (temp)
		//{
		//	//i didn't know it's possible :O
		//	priorityQueue.addToHeap({ i, temp->getValue(), temp->getWeight() });
		//	temp = temp->getNext();
		//}
	}

	int from = 0, to = 0;
	bool found = false;
	for (int i = 0; i< edges; i++)
	{
		for (int j = 0; j< vertices; j++)
		{
			if (!found && tab[i][j] != 0)
			{
				from = j;
				found = true;
			}
			else if (found && tab[i][j] != 0)
			{
				to = j;
				found = false;
				break;
			}
		}
		priorityQueue.addToHeap({ from, to, tab[i][from] });
		found = false;
		to = 0, from = 0;
	}

	//array for final tree
	BinaryHeap tree = BinaryHeap();

	for (int i = 1; i < priorityQueue.getSize(); i++)
	{
		if (checked[priorityQueue.getRoot().from]->getValue() != checked[priorityQueue.getRoot().to]->getValue())
		{
			//add edge to tree
			tree.addToHeap({ priorityQueue.getRoot().from , priorityQueue.getRoot().to , priorityQueue.getRoot().weight });
			//connect subtrees
			int subtreeIdx = checked[priorityQueue.getRoot().to]->getValue();
			for (int j = 0; j < checked.getCount(); j++)
			{
				//if number of subtree is the same as second subtree
				//set this number to number of first subtree
				if (checked[j]->getValue() == subtreeIdx)
				{
					checked[j]->setValue(checked[priorityQueue.getRoot().from]->getValue());
				}
			}
		}
		priorityQueue.deleteRoot();
	}

	int distance = 0;
	//std::cout << "Drzewo: " << std::endl;
	for (int i = 0; i < tree.getSize(); i++)
	{
		distance += tree[i].weight;
		//std::cout << tree[i].from << "->" << tree[i].to << "[" << tree[i].weight << "]" << std::endl;
	}

	return distance;
}

int Matrix::bellman_ford(int from, int to, bool directed)
{
	struct bfEdge
	{
		int distance = 1000;
		int previous = -1;
	};

	bfEdge* verticesBF = new bfEdge[vertices];
	verticesBF[from] = { 0, from };
	bool test = true;
	int findTo = 0;
	int tempFrom = 0;
	int tempTo = 0;
	bool found = 0;

	for (int i = 0; i < vertices - 1; i++)
	{
		test = true;
		for (int j = 0; j < edges; j++)
		{
			found = false;
			tempFrom = -1;
			tempTo = -1;
			for (int k = 0; k < vertices; k++)
			{

				if (!found && tab[j][k] < 0)
				{
					tempFrom = k;
					found = true;
				}
				else if (!found && tab[j][k] > 0)
				{
					tempTo = k;
					found = true;
				}
				else if (found && tab[j][k] < 0 && k != tempTo)
				{
					tempFrom = k;
					test = false;
					break;
					
				}
				else if (found && tab[j][k] > 0 && k != tempFrom)
				{
					tempTo = k;
					test = false;
					break;
				}
			}

			if (verticesBF[tempFrom].distance + abs(static_cast<double>(tab[j][tempTo])) < verticesBF[tempTo].distance)
			{
				test = false;	
				verticesBF[tempTo].distance = verticesBF[tempFrom].distance + abs(static_cast<double>(tab[j][tempTo]));
				verticesBF[tempTo].previous = tempFrom;
			}
		}
		if (test) break;
	}

	int now = to;
	int dist = verticesBF[now].distance;

	//std::cout << "DROGA" << std::endl;
	while (now != from)
	{
		//std::cout << now << ", ";
		now = verticesBF[now].previous;
	}
	//std::cout << from << std::endl;

	delete[] verticesBF;

	return dist;
}

Matrix& Matrix::operator=(const Matrix& m)
{
	if (this == &m)
	{
		return *this;
	}
	
	this->edges = m.edges;
	this->vertices = m.vertices;

	this->tab = new int*[edges];
	for (int i = 0; i < edges; i++)
	{
		this->tab[i] = new int[vertices];
	}

	for (int i = 0; i < edges; i++)
	{
		for (int j = 0; j < vertices; j++)
		{
			this->tab[i][j] = m.tab[i][j];
		}
	}

	return *this;
}
