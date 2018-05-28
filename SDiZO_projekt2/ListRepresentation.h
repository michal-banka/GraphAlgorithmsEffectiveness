#pragma once
#include "Libs.h"
#include "BidirectionalListManagment.h"

class List
{
private:
	BidirectionalListManagement* list;
	int vertices;
	int edges;
public:
	List();
	List(BidirectionalListManagement* list, int vertices, int edges);
	~List();

	void addVertex();
	void removeVertex(int index);
	//TODO
	//remember about making variable directed in menu
	//every algotihm will have own const directed
	void addEdge(int fromVertex, int toVertex, int weight, bool directed);
	void removeEdge(int fromVertex, int toVertex, bool directed);
};

