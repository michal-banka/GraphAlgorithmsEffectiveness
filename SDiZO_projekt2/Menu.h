#pragma once
#include "MatrixRepresentation.h"
#include "ListRepresentation.h"
#include "Graph.h"

class Menu
{
private:
	Graph graph;
public:
	Menu();
	Menu(bool directed);
	~Menu();

	void menu();
	
	// possible change of idea
	//void matrixMenu();
};

