#pragma once
#include "ListRepresentation.h"
#include "MatrixRepresentation.h"

class Graph
{
private:
	List listRepresentation;
	Matrix matrixRepresentation;
	bool directed;

public:
	Graph();
	Graph(bool directed);
	Graph(List listRepresentation, Matrix matrixRepresentation,bool directed);
	~Graph();

	void addVertex();
	void removeVertex();
	void removeVertex(int n);
	void addEdge();
	void addEdge(int fromVertex, int toVertex, int weight);
	void removeEdge();
	void removeEdge(int fromVertex, int toVertex);

	void showRepresentations();

	void fillRandom();
	void fillRandom(int vertices, int density, int weightRange);
	void fillFromFile();
	void fillFromFile(std::string filename);
};

