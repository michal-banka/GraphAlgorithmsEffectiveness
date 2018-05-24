#pragma once
#include "Libs.h"
class Matrix
{
private:
	int** table2d;
	//number of vertices
	int vertex;
public:
	Matrix(int vertex);
	~Matrix();

	void addNNewVertex(int n);
	/* TO DO
	void addNNewVertex();
	void removeVertex();
	void removeVertex(int n);*/
	void insertEdge();
	void insertEdge(int fromVertex, int toVertex, int weight);
	void removeEdge();
	void removeEdge(int fromVertex, int toVertex);
};

