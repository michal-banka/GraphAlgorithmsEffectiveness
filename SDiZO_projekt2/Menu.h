#pragma once
#include "MatrixRepresentation.h"
#include "ListRepresentation.h"
#include "Graph.h"

class Menu
{
private:
	Graph graph;
	TimeCounter time;
public:
	Menu();
	Menu(bool directed);
	~Menu();

	void menu();
	void editMenu();
	
	// possible change of idea
	//void matrixMenu();
};

