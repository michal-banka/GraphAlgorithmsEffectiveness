#pragma once
#include "ListRepresentation.h"
#include "MatrixRepresentation.h"
#include "TimeCounter.h"

class Graph
{
private:
	List listRepresentation;
	Matrix matrixRepresentation;
	bool directed;

	TimeCounter timeCounter;
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
	void clearAll();
	bool isDirected();
	void setDirection(bool direction);
	int getVertices();
	void editEdge(int from, int to, int weight);

	void fillRandom();
	void fillRandom(int vertices, int density, int weightRange);
	void fillFromFile();
	void fillFromFile(std::string filename);
	void saveTableToFile(std::string filename, std::string header, int rows, int columns, double** tab);

	void dijkstra();
	void dijkstra(int from, int to);
	void prim();
	void prim(int from);
	void kruskal();
	void bellman_ford();
	void bellman_ford(int from, int to);

	void test();
};

