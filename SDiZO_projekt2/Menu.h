#pragma once
#include "Matrix.h"


class Menu
{
private:
	Matrix matrixRepresentation;

public:
	Menu();
	~Menu();

	void showMenu();
	void minimalSpanningTree();
	
	// possible change of idea
	//void matrixMenu();
};

