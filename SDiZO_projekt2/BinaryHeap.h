#pragma once
#include "Libs.h"
#include "TimeCounter.h"

struct kruskalEdge
{
	int from = 0;
	int to = 0;
	int weight = 0;
};

class BinaryHeap
{
private:
	TimeCounter counter;
	kruskalEdge* heap;
	int size;
public:
	BinaryHeap();
	BinaryHeap(int size);
	~BinaryHeap();

	int getParentIdx(int idxSon);
	int getLeftSonIdx(int idxParent);
	int getRightSonIdx(int idxParent);
	void swapElementsInHeap(int idx1, int idx2);
	int getSize();

	void addToHeap(kruskalEdge edge);
	kruskalEdge getRoot();
	void showHeap();
	void deleteRoot();

	kruskalEdge& operator[](const int& i);
};

