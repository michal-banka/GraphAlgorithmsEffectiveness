#pragma once
#include "Libs.h"
class Matrix
{
private:
	int** tab;
	//number of vertices
	int vertices;
	int edges;
public:
	Matrix();
	Matrix(int vertices, int edges);
	~Matrix();

	int getVertices();
	int getEdges();

	void addVertex();
	void removeVertex();
	void removeVertex(int n);
	
	void addEdge();
	void addEdge(int fromVertex, int toVertex, int weight, bool directed);
	void removeEdge();
	void removeEdge(int fromVertex, int toVertex, bool directed);

	void show();

	/* TODO
	*/
};

