#include "BinaryHeap.h"
#include <commdlg.h>


BinaryHeap::BinaryHeap()
{
	this->size = 0;
	this->heap = nullptr;
}

BinaryHeap::BinaryHeap(int size)
{
	this->size = size;
	this->heap = new kruskalEdge[size];
	for(int i = 0; i < size; i++)
	{
		heap[i] = kruskalEdge();
	}
}

BinaryHeap::~BinaryHeap()
{
	delete[] heap;
}

int BinaryHeap::getParentIdx(int idxSon)
{
	if ((idxSon - 1) / 2 < 0) return 0;
	return (idxSon - 1) / 2;
}

int BinaryHeap::getLeftSonIdx(int idxParent)
{
	if (2 * idxParent + 1 >= size) return -1;
	return 2 * idxParent + 1;
}

int BinaryHeap::getRightSonIdx(int idxParent)
{
	if (2 * idxParent + 2 >= size) return -1;
	return 2 * idxParent + 2;
}

void BinaryHeap::swapElementsInHeap(int idx1, int idx2)
{
	if (idx1 < 0 || idx1 >= size || idx2 < 0 || idx2 >= size) return;

	kruskalEdge temp = heap[idx1];
	heap[idx1] = heap[idx2];
	heap[idx2] = temp;
}

int BinaryHeap::getSize()
{
	return this->size;
}

void BinaryHeap::addToHeap(kruskalEdge edge)
{
	int now = 0;
	this->size++;

	kruskalEdge* temp = new kruskalEdge[size];
	for (int i = 0; i < size - 1; i++)
	{
		temp[i] = heap[i];
	}
	temp[size - 1] = edge;

	delete heap;
	heap = temp;

	int idx1 = size - 1;
	int idx2 = getParentIdx(size - 1);
	while (heap[idx1].weight < heap[idx2].weight)
	{
		swapElementsInHeap(idx1, idx2);
		idx1 = idx2;
		idx2 = getParentIdx(idx2);
	}
}

kruskalEdge BinaryHeap::getRoot()
{
	return heap[0];
}

void BinaryHeap::showHeap()
{
	int p = 1;
	for(int i = 0 ; i < size; i++)
	{
		std::cout << heap[i].from << "->" << heap[i].to << "[" << heap[i].weight << "]\t";
		if (i + 1 == pow(2,p) - 1)
		{
			p++;
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}


void BinaryHeap::deleteRoot()
{
	if (size != 0)
	{
		size--;
		kruskalEdge last = heap[size];
		int i = 0, j = 1;
		while(j < size)
		{
			if (j+1 < size && heap[j+1].weight < heap[j].weight)
			{
				j++;
			}
			if (last.weight <= heap[j].weight)
			{
				break;
			}
			heap[i] = heap[j];
			i = j;
			j = 2 * j + 1;
		}
		heap[i] = last;
	}
	else
	{
		std::cout << "[INFO]Heap is empty. Root has NOT been deleted." << std::endl;
	}
}

kruskalEdge& BinaryHeap::operator[](const int& i)
{
	return this->heap[i];
}
