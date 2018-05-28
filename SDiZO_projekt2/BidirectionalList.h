#pragma once
#include "Libs.h"

class BidirectionalList
{
private:
	//in this project value will represent index of vertex at the end of  the edge
	int value;
	//weight is weight of the edge
	int weight;
	BidirectionalList* next;
	BidirectionalList* prev;
public:
	BidirectionalList();
	BidirectionalList(BidirectionalList* next, BidirectionalList* prev);
	BidirectionalList(BidirectionalList* next, BidirectionalList* prev, int value);
	~BidirectionalList();

	BidirectionalList* getNext();
	BidirectionalList* getPrev();
	int getValue();
	void setNext(BidirectionalList* next);
	void setPrev(BidirectionalList* prev);
	void setValue(int value);
	int getWeight();
	void setWeight(int weight);
	

};