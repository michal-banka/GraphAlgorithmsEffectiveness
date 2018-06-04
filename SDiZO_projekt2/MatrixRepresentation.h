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
	int numberOfEdgesOf(int vertex);

	void addVertex();
	void removeVertex();
	void removeVertex(int n);
	void editEdge(int from, int to, int newWeight);
	void addEdge();
	void addEdge(int fromVertex, int toVertex, int weight, bool directed);
	void removeEdge();
	void removeEdge(int fromVertex, int toVertex, bool directed);

	void show();

	int dijkstra(int from, int to, bool directed);
	int prim(int from);
	int prim2(int from);
};

