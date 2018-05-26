#pragma once
#include "Libs.h"
class Matrix
{
private:
	int** table2d;
	//number of vertices
	int vertex;
public:
	Matrix();
	Matrix(int vertex);
	~Matrix();

	void addNNewVertex();
	void addNNewVertex(int n);
	void removeVertex();
	void removeVertex(int n);
	
	void addEdge();
	void addEdge(int fromVertex, int toVertex, int weight);
	void removeEdge();
	void removeEdge(int fromVertex, int toVertex);

	void showMatrix();

	/* TO DO
	*/
};

