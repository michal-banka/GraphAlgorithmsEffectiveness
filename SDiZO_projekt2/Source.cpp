#include "Libs.h"
#include "Menu.h"
#include "Graph.h"

int main()
{
	//TODO
	//change language of Bidircetional classes' methods to Polish (?) 
	//Menu menu;
	//menu.showMenu();

	Graph graph;
	graph.showRepresentations();
	graph.addVertex();
	graph.addVertex();
	graph.addVertex();
	graph.addVertex();
	graph.addEdge(0, 2, 4, true);
	graph.showRepresentations();
	std::cin.get();
	return 0;
}
