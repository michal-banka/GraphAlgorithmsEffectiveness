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
	//Menu menu;
	//menu.showMenu();
	Graph graph;
	graph.showRepresentations();
	graph.fillFromFile();
	graph.showRepresentations();

	std::cin.get();
	return 0;
}
