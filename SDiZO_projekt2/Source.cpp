#include "Libs.h"
#include "Menu.h"
#include "Graph.h"

int main()
{
	srand(time(nullptr));
	//TODO
	//change language of Bidircetional classes' methods to Polish (?)
	//create algorithms in Graph class
	//create menu
	//do graph to be consistent (!)
	Graph graph(true);
	graph.showRepresentations();
	//graph.fillRandom();
	graph.fillFromFile("data2.txt");
	graph.showRepresentations();
	graph.dijkstra();

	std::cin.get();
	return 0;
}
