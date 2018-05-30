#pragma once
#include "ListRepresentation.h"
#include "MatrixRepresentation.h"

class Graph
{
private:
	List listRepresentation;
	Matrix matrixRepresentation;
	int vertices;
	int edges;
public:
	Graph();
	Graph(List listRepresentation, Matrix matrixRepresentation);
	~Graph();

	void addVertex();
	void removeVertex();
	void removeVertex(int n);
	void addEdge();
	void addEdge(int fromVertex, int toVertex, int weight, bool directed);
	void removeEdge();

	void showRepresentations();
};

