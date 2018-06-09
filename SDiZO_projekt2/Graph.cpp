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
	//std::cout << "d = " << d << std::endl;
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
	}

	//add more edges if needed
	for (int i = edgesInMatrix; i < edges; i++)
	{
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
	//ok std::cout << "edges = " << edgesInMatrix << std::endl;
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
		std::cout << "Blad odczytu pliku " << filename << std::endl;
	}

	read.close();
}

void Graph::saveTableToFile(std::string filename, std::string header, int rows, int columns, double** tab)
{
	std::ofstream save;
	save.open(filename);
	if (save.is_open())
	{
		save << header << std::endl;
		for(int i = 0 ;i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				save << tab[i][j] << "\t";
			}
			save << std::endl;
		}
	}
	else
	{
		std::cout << "Nie udalo sie otworzyc pliku do zapisu: " << filename << std::endl;
	}
	save.close();
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
	//std::cout << "Algorytm Dijkstry:" << std::endl;
	int list = listRepresentation.dijkstra(from, to);
	int matrix = matrixRepresentation.dijkstra(from, to, directed);

	std::cout << "Dystans - Lista = " << list << std::endl;
	std::cout << "Dystans - Matrix = " << matrix << std::endl;
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

void Graph::kruskal()
{
	std::cout << "Algorytm Kriskala: " << std::endl;
	std::cout << "\tLista - waga drzewa: " << listRepresentation.kruskal() << std::endl;
	std::cout << "\tMacierz - waga drzewa: " << matrixRepresentation.kruskal() << std::endl;
}

void Graph::bellman_ford()
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
	bellman_ford(from, to);
}

void Graph::bellman_ford(int from, int to)
{
	int list = listRepresentation.bellman_ford(from, to);
	std::cout << "Dystans - Lista: " << list << std::endl;
	int matrix = matrixRepresentation.bellman_ford(from, to, directed);
	std::cout << "Dystans - Matrix: " << matrix << std::endl;
}

void Graph::test()
{
	//TODO
	//set graph to directed, becouse dijkstra should be tested on directed graph
	directed = true;

	double** timesDijkstraTab = new double*[4];
	double** timesDijkstraList = new double*[4];
	double** timesPrimTab = new double*[4];
	double** timesPrimList = new double*[4];
	double** timesKruskalTab = new double*[4];
	double** timesKruskalList = new double*[4];
	double** timesBellmanTab = new double*[4];
	double** timesBellmanList = new double*[4];

	for (int i = 0 ; i < 4; i++)
	{
		timesDijkstraList[i] = new double[5];
		timesDijkstraTab[i] = new double[5];
		timesPrimList[i] = new double[5];
		timesPrimTab[i] = new double[5];
		timesKruskalList[i] = new double[5];
		timesKruskalTab[i] = new double[5];
		timesBellmanList[i] = new double[5];
		timesBellmanTab[i] = new double[5];

		for(int j = 0; j < 5; j++)
		{
			timesDijkstraList[i][j] = 0;
			timesDijkstraTab[i][j] = 0;
			timesPrimList[i][j] = 0;
			timesPrimTab[i][j] = 0;
			timesKruskalList[i][j] = 0;
			timesKruskalTab[i][j] = 0;
			timesBellmanList[i][j] = 0;
			timesBellmanTab[i][j] = 0;
		}
	}

	int densities[] = {25, 50, 75, 99};
	int sizes[] = {20,40,60,80,100};

	//Dijkstra

	std::cout << "DIJKSTRA AND BELLMAN-FORD TEST:" << std::endl;
	//check different densities
	//25, 50, 75, 99
	for(int i = 0 ;i < 4; i++)
	{
		//check different sizes
		//25,50,75,100,125
		for (int j = 0; j < 5; j++)
		{
			//get 100 samples to get average time later
			for (int k = 0; k < 100; k++)
			{
				std::cout << "[DIJKSTRA/BELLMAN-FORD]Density = " << densities[i] << ", size = " << sizes[j] << " - " << k + 1 << " / 100" << std::endl;
				fillRandom(sizes[j], densities[i], 50);

				timeCounter.start();
				matrixRepresentation.dijkstra(0, sizes[j] - 1, directed);
				timesDijkstraTab[i][j] += timeCounter.stop();

				timeCounter.start();
				listRepresentation.dijkstra(0, sizes[j] - 1);
				timesDijkstraList[i][j] += timeCounter.stop();

				timeCounter.start();
				matrixRepresentation.bellman_ford(0, sizes[j] - 1, directed);
				timesBellmanTab[i][j] += timeCounter.stop();

				timeCounter.start();
				listRepresentation.bellman_ford(0, sizes[j] - 1);
				timesBellmanList[i][j] += timeCounter.stop();
			}
		}
	}

	directed = false;

	//Prim and Kruskal
	std::cout << "PRIM AND KRUSKAL TEST:" << std::endl;
	//check different densities
	//25, 50, 75, 99
	for (int i = 0; i < 4; i++)
	{
		//check different sizes
		//25,50,75,100,125
		for (int j = 0; j < 5; j++)
		{
			//get 100 samples to get average time later
			for (int k = 0; k < 100; k++)
			{
				std::cout << "[PRIM/KRUSKAL]Density = " << densities[i] << ", size = " << sizes[j] << " - " << k + 1 << " / 100" << std::endl;
				fillRandom(sizes[j], densities[i], 50);

				timeCounter.start();
				matrixRepresentation.prim2(0);
				timesPrimTab[i][j] += timeCounter.stop();

				timeCounter.start();
				listRepresentation.prim2(0);
				timesPrimList[i][j] += timeCounter.stop();

				timeCounter.start();
				matrixRepresentation.kruskal();
				timesKruskalTab[i][j] += timeCounter.stop();

				timeCounter.start();
				listRepresentation.kruskal();
				timesKruskalList[i][j] += timeCounter.stop();
			}
		}
	}

	//show dijkstra matrix
	std::cout << "Dijkstra average times - Tab" << std::endl;
	std::cout << "\t25\t50\t75\t100\t125" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << densities[i] << ":\t";
		for (int j = 0; j < 5; j++)
		{
			std::cout << timesDijkstraTab[i][j] << "\t";
		}
		std::cout << std::endl;
	}

	saveTableToFile("dijkstraMatrix.txt", "Dijkstra total times - Matrix - (divide by 100 to get average)", 4, 5, timesDijkstraTab);

	//show dijkstra list
	std::cout << "Dijkstra average times - List" << std::endl;
	std::cout << "\t25\t50\t75\t100\t125" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << densities[i] << ":\t";
		for (int j = 0; j < 5; j++)
		{
			std::cout << timesDijkstraList[i][j] << "\t";
		}
		std::cout << std::endl;
	}

	saveTableToFile("dijkstraList.txt", "Dijkstra total times - List - (divide by 100 to get average)", 4, 5, timesDijkstraList);

	//show Bellman_Ford matrix
	std::cout << "Bellman_Ford average times - Tab" << std::endl;
	std::cout << "\t25\t50\t75\t100\t125" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << densities[i] << ":\t";
		for (int j = 0; j < 5; j++)
		{
			std::cout << timesBellmanTab[i][j] << "\t";
		}
		std::cout << std::endl;
	}

	saveTableToFile("Bellman_FordMatrix.txt", "Bellman_Ford total times - Matrix - (divide by 100 to get average)", 4, 5, timesBellmanTab);

	//show Bellman_Ford list
	std::cout << "Bellman_Ford average times - List" << std::endl;
	std::cout << "\t25\t50\t75\t100\t125" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << densities[i] << ":\t";
		for (int j = 0; j < 5; j++)
		{
			std::cout << timesBellmanList[i][j] << "\t";
		}
		std::cout << std::endl;
	}

	saveTableToFile("Bellman_FordList.txt", "Bellman_Ford total times - List - (divide by 100 to get average)", 4, 5, timesBellmanList);

	//show prim list
	std::cout << "Prim average times - List" << std::endl;
	std::cout << "\t25\t50\t75\t100\t125" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << densities[i] << ":\t";
		for (int j = 0; j < 5; j++)
		{
			std::cout << timesPrimList[i][j] << "\t";
		}
		std::cout << std::endl;
	}

	saveTableToFile("primList.txt", "Prim total times - List - (divide by 100 to get average)", 4, 5, timesPrimList);

	//show prim matrix
	std::cout << "Prim average times - Matrix" << std::endl;
	std::cout << "\t25\t50\t75\t100\t125" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << densities[i] << ":\t";
		for (int j = 0; j < 5; j++)
		{
			std::cout << timesPrimTab[i][j] << "\t";
		}
		std::cout << std::endl;
	}

	saveTableToFile("primMatrix.txt", "Prim total times - Matrix - (divide by 100 to get average)", 4, 5, timesPrimTab);

	//show kruskal list
	std::cout << "Kruskal average times - List" << std::endl;
	std::cout << "\t25\t50\t75\t100\t125" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << densities[i] << ":\t";
		for (int j = 0; j < 5; j++)
		{
			std::cout << timesKruskalList[i][j] << "\t";
		}
		std::cout << std::endl;
	}

	saveTableToFile("kruskalList.txt", "Kruskal total times - List - (divide by 100 to get average)", 4, 5, timesKruskalList);

	//show Kruskal matrix
	std::cout << "Kruskal average times - Matrix" << std::endl;
	std::cout << "\t25\t50\t75\t100\t125" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cout << densities[i] << ":\t";
		for (int j = 0; j < 5; j++)
		{
			std::cout << timesKruskalTab[i][j] << "\t";
		}
		std::cout << std::endl;
	}

	saveTableToFile("kruskalMatrix.txt", "Kruskal total times - Matrix - (divide by 100 to get average)", 4, 5, timesKruskalTab);


	//destructors
	for (int i = 0 ; i < 4; i++)
	{
		delete[] timesBellmanList[i];
		delete[] timesBellmanTab[i];
		delete[] timesDijkstraList[i];
		delete[] timesDijkstraTab[i];
		delete[] timesKruskalList[i];
		delete[] timesKruskalTab[i];
		delete[] timesPrimList[i];
		delete[] timesPrimTab[i];
	}

	delete[] timesBellmanList;
	delete[] timesBellmanTab;
	delete[] timesDijkstraList;
	delete[] timesDijkstraTab;
	delete[] timesKruskalList;
	delete[] timesKruskalTab;
	delete[] timesPrimList;
	delete[] timesPrimTab;
}
