#include "BidirectionalList.h"



BidirectionalList::BidirectionalList()
{
	this->next = nullptr;
	this->prev = nullptr;
	this->value = 0;
	this->weight = 0;
}

BidirectionalList::BidirectionalList(BidirectionalList* next, BidirectionalList* prev)
{
	int value = 0;
	std::cout << "Value: ";
	std::cin >> value;
	std::cin.get();
	this->next = next;
	this->prev = prev;
	this->weight = 0;
}

BidirectionalList::BidirectionalList(BidirectionalList* next, BidirectionalList* prev, int value, int weight)
{
	this->next = next;
	this->prev = prev;
	this->value = value;
	this->weight = weight;
}

BidirectionalList::~BidirectionalList()
{
	delete next;
	delete prev;
}

BidirectionalList * BidirectionalList::getNext()
{
	return this->next;
}

BidirectionalList * BidirectionalList::getPrev()
{
	return this->prev;
}

int BidirectionalList::getValue()
{
	return this->value;
}

void BidirectionalList::setNext(BidirectionalList * next)
{
	this->next = next;
}

void BidirectionalList::setPrev(BidirectionalList * prev)
{
	this->prev = prev;
}

void BidirectionalList::setValue(int value)
{
	this->value = value;
}

int BidirectionalList::getWeight()
{
	return this->weight;
}

void BidirectionalList::setWeight(int weight)
{
	this->weight = weight;
}


