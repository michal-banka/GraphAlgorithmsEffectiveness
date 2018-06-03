#include "Libs.h"
#include "Menu.h"
#include "Graph.h"

int main()
{
	srand(time(nullptr));
	//TODO
	//change language of Bidircetional classes' methods to Polish (?)
	//create algorithms in Graph class
	//check destructors and deleting temps
	//do graph to be consistent (!)

	Menu menu;
	menu.menu();
	std::cin.get();
	return 0;
}
