#pragma once
#include "Libs.h"
#include "BidirectionalListManagment.h"

class List
{
private:
	BidirectionalListManagement* list;
	int vertices;
public:
	List();
	List(BidirectionalListManagement* list, int vertices);
	~List();

	int getVertices();

	void addVertex();
	void removeVertex();
	void removeVertex(int index);

	void addEdge();
	void addEdge(int fromVertex, int toVertex, int weight, bool directed);
	void removeEdge();
	void removeEdge(int fromVertex, int toVertex, bool directed);
	
	bool doesEdgeExists(int fromVertex, int toVertex);


	void show();
};

