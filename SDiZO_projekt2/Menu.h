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
	void menuShortestPath();
	void menuMSP();
	void editMenu();
	
	// possible change of idea
	//void matrixMenu();
};

