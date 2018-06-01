#pragma once
#include "Libs.h"
#include "BidirectionalList.h"

//in this project class represents vertex
//BidirectionalList class represents all edges of this vertex
class BidirectionalListManagement
{
private:
	BidirectionalList* head;
	BidirectionalList* tail;
	int count = 0;

public:
	BidirectionalListManagement();
	BidirectionalListManagement(int count);
	~BidirectionalListManagement();

	//getters and setters
	BidirectionalList* getHead();
	BidirectionalList* getTail();
	int getCount();
	void setHead(BidirectionalList* head);
	void setTail(BidirectionalList* tail);
	void setCount(int count);

	//functions, all with argument and without
	void addNewElementBegin(int value, int weight);
	void addNewElementEnd(int value, int weight);
	void addNewElementAnyWhere(int value, int weight, int position);
	void addNewElement();
	void addNewElement(int value, int weight, int position);

	void showList();

	void deleteElementBegin();
	void deleteElementEnd();
	void deleteElementAnywhere(int position);
	void deleteElement();
	void deleteElement(int position);

	int findElementPos();
	int findElementPos(int value);
	
	//function add elements from file to existing list
	void fillFromFile();
	void fillFromFile(std::string filename);
	void saveToFile();
	void saveToFile(std::string filename);
	void appendDoubleToTextFile(std::string filename, double dataToAppend);

	//functions which return time of operations
	void addNRandomElementsToList();
	void addNRandomElementsToList(int position, int n, int rangeDown, int rangeUp);

	void deleteAll();
	void deleteAll(int position);

	void findElementTime();
	void findElementTime(int value);

	bool doesValueExist(int value);
	int getMinimumValueIndex(int value);

	BidirectionalList* & operator[](int el);
};

