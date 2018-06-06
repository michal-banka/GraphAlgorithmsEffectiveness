#pragma once
#include "Libs.h"
class Matrix
{
private:
	int** tab;

	int edges;
	int vertices;
public:
	Matrix();
	Matrix(int vertices, int edges);
	Matrix(int** tab, int vertices, int edges);
	Matrix(const Matrix& m);
	~Matrix();

	int getVertices();
	int getEdges();
	void setTab(int** tab);
	void setEdges(int edges);
	void setVertices(int vertices);
	void setValueOnMatrix(int edge, int vertex, int value);
	
	int numberOfEdgesOf(int vertex);
	bool doesEdgeExist(int from, int to);

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

	Matrix& operator= (const Matrix& m);
};

