#include "BidirectionalListManagment.h"



BidirectionalListManagement::BidirectionalListManagement()
{
	this->head = nullptr;
	this->tail = nullptr;
	this->count = 0;
}

BidirectionalListManagement::BidirectionalListManagement(int count)
{
	this->head = NULL;
	this->tail = NULL;
	this->count = count;

	for (int i = 0 ; i < count; i++)
	{
		addNewElementEnd(0, 1);
	}
}


BidirectionalListManagement::~BidirectionalListManagement()
{
	//deleteAll(0);
	delete head;
	delete tail;
}

BidirectionalList * BidirectionalListManagement::getHead()
{
	return this->head;
}

BidirectionalList * BidirectionalListManagement::getTail()
{
	return this->tail;
}

int BidirectionalListManagement::getCount()
{
	return this->count;
}

void BidirectionalListManagement::setHead(BidirectionalList * head)
{
	this->head = head;
}

void BidirectionalListManagement::setTail(BidirectionalList * tail)
{
	this->tail = tail;
}

void BidirectionalListManagement::setCount(int count)
{
	this->count = count;
}


void BidirectionalListManagement::addNewElementBegin(int value, int weight)
{
	BidirectionalList* newElem = new BidirectionalList();
	newElem->setValue(value);
	newElem->setWeight(weight);

	//if list is empty
	if (head == nullptr)
	{
		head = newElem;
		tail = newElem;
	}
	else
	{
		newElem->setNext(head);
		head = newElem;
		head->getNext()->setPrev(newElem);
	}
	count++;
}


void BidirectionalListManagement::addNewElementEnd(int value, int weight)
{
	BidirectionalList* newElem = new BidirectionalList();
	newElem->setValue(value);
	newElem->setWeight(weight);

	//if list is empty (never occur)
	if (!head)
	{
		newElem->setPrev(nullptr);
		newElem->setNext(nullptr);
		head = newElem;
		tail = newElem;
	}
	else
	{
		newElem->setPrev(tail);
		tail->setNext(newElem);
		tail = newElem;
	}
	count++;
}

void BidirectionalListManagement::addNewElementAnyWhere(int value, int weight, int position)
{
	BidirectionalList* newElem;
	BidirectionalList* pointer;

	newElem = new BidirectionalList;
	pointer = getHead();
	for (int i = 0; i < position; i++)
	{
		pointer = pointer->getNext();
	}
	newElem->setNext(pointer);
	newElem->setPrev(pointer->getPrev());
	newElem->setValue(value);
	newElem->setWeight(weight);
	pointer->getPrev()->setNext(newElem);
	pointer->setPrev(newElem);
	count++;
}

//this is main function to add new element
//rest are only for faster adding to list with different algorithm
void BidirectionalListManagement::addNewElement()
{
	int val = 0;
	int pos = 0;
	int w = 0;

	std::cout << "Value of new element: ";
	std::cin >> val;
	std::cin.get();

	std::cout << "Weight of new element: ";
	std::cin >> w;
	std::cin.get();

	do
	{
		std::cout << "Position of new element (0 - " << count << "):";
		std::cin >> pos;
		std::cin.get();
	} while (pos < 0 || pos > count);

	addNewElement(val, w, pos);
}

//same as upper method but with arguments
void BidirectionalListManagement::addNewElement(int value,  int weight, int position)
{
	// "index" of new element, count is index of one after last so it will be new end
	if (position >=0 && position <= count)
	{
		//usage of different methods
		if (position == 0)
		{
			addNewElementBegin(value, weight);
		}
		else if (position == count)
		{
			addNewElementEnd(value, weight);
		}
		else
		{
			addNewElementAnyWhere(value, weight, position);
		}
	}
	else
	{
		std::cout << "[INFO] Position is out of list. Element has NOT been added." << std::endl << std::endl;
	}
}

void BidirectionalListManagement::showList()
{
	if (head)
	{
		BidirectionalList* headTemp = getHead();

		std::cout << "====LIST====" << std::endl;
		int i = 0;
		while (headTemp)
		{
			std::cout << "List[" << i << "] = " << headTemp->getValue() << std::endl;
			headTemp = headTemp->getNext();
			i++;
		}
		std::cout << "============" << std::endl;
	}
	else
	{
		std::cout << "List is empty." << std::endl;
	}
}

void BidirectionalListManagement::deleteElementBegin()
{
	//if that's only element in list
	if (count == 1)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else
	{
		head = head->getNext();
		delete head->getPrev();
		head->setPrev(nullptr);
	}
	count--;
}

void BidirectionalListManagement::deleteElementEnd()
{
	//this function doesn't check size of list
	//if count > 1 this function is correct
	//if count = 1 it would work excatly the same as deleteFromBegin so it will be used
	tail = tail->getPrev();
	delete tail->getNext();
	tail->setNext(nullptr);
	count--;
}

void BidirectionalListManagement::deleteElementAnywhere(int position)
{
	BidirectionalList* temp = getHead();
	for (int i = 0; i < position; i++)
	{
		temp = temp->getNext();
	}
	temp->getNext()->setPrev(temp->getPrev());
	temp->getPrev()->setNext(temp->getNext());
	delete temp;
	count--;
}

void BidirectionalListManagement::deleteElement()
{
	if (count > 0)
	{
		int pos = 0;
		do
		{
			std::cout << "Position of element to delete (0 - " << count - 1 << "):";
			std::cin >> pos;
			std::cin.get();

			deleteElement(pos);
		} while (pos < 0 || pos >= count);
	}
	else
	{
		std::cout << "[INFO] List is empty, nothing to delete." << std::endl;
	}
}


void BidirectionalListManagement::deleteElement(int position)
{
	if (head && position >= 0)
	{
		//delete first element
		if(position == 0)
		{
			deleteElementBegin();
		}
		//delete last element
		else if (position == count - 1)
		{
			deleteElementEnd();
		}
		//delete from inside of list
		else
		{
			deleteElementAnywhere(position);
		}
	}
	else
	{
		std::cout << "[INFO] List is empty, nothing to delete." << std::endl;
	}
}

int BidirectionalListManagement::findElementPos()
{
	int val = 0;
	std::cout << "Value of element to find: ";
	std::cin >> val;
	std::cin.get();


	return findElementPos(val);
}

int BidirectionalListManagement::findElementPos(int value)
{
	BidirectionalList* temp = getHead();
	int pos = 0;
	while (temp)
	{
		if(temp->getValue() == value)
		{
			return pos;
		}
		pos++;
		temp = temp->getNext();
	}
	return -1;
}



void BidirectionalListManagement::fillFromFile()
{
	std::string name = "";
	std::cout << "Insert file name (without extension): ";
	std::cin >> name;
	std::cin.get();

	fillFromFile(name);
}

void BidirectionalListManagement::fillFromFile(std::string filename)
{
	int value = 0;
	int weight = 0;
	filename += ".txt";
	std::ifstream read;

	read.open(filename);
	if (read.is_open())
	{
		std::cout << "[INFO] File has been opened." << std::endl;
		while (!read.eof())
		{
			read >> value;
			read >> weight;
			addNewElementEnd(value, weight);
		}
		std::cout << "[INFO] Filling list finished." << std::endl;
	}
	else
	{
		std::cout << "[INFO] File has NOT been opened. List is not filled." << std::endl;
	}
	read.close();
}

void BidirectionalListManagement::saveToFile()
{
	std::string name = "";
	std::cout << "Insert file name to save (without extension): ";
	std::cin >> name;
	std::cin.get();

	saveToFile(name);
}

void BidirectionalListManagement::saveToFile(std::string filename)
{
	filename += ".txt";
	std::ofstream write;
	write.open(filename);
	if (write.is_open())
	{
		//weird look but cool work
		for (BidirectionalList* temp = getHead(); temp; temp = temp->getNext())
		{
			write << temp->getValue() << std::endl;
		}
		std::cout << "[INFO] List saved to file." << std::endl;
	}
	else
	{
		std::cout << "[INFO] File could NOT be created/opened. " << std::endl;
	}
}

void BidirectionalListManagement::appendDoubleToTextFile(std::string filename, double dataToAppend)
{
	std::ofstream append;
	append.open(filename, std::ios::app);
	if (append.is_open())
	{
		append << dataToAppend << std::endl;
	}
	else
	{
		std::cout << "[INFO] File could NOT be created or opened. Nothing has been appended." << std::endl;
	}
	append.close();
}

void BidirectionalListManagement::addNRandomElementsToList()
{
	int choice = 0;
	int position = 0;
	int n = 0;
	int down = 0;
	int up = 0;

	std::cout << "1. Add every new element to the beggining.\n" <<
		"2. Add every new element to the end.\n" <<
		"3. Add every new element to position...\n";
	do
	{
		std::cout << "Your choice: ";
		std::cin >> choice;
		std::cin.get();
	} while (choice < 1 || choice > 3);

	if (choice == 1) position = 0;
	else if (choice == 2) position = count;
	else
	{
		std::cout << "Position of elements to add (0 - " << count << "): ";
		std::cin >> position;
		std::cin.get();
	}

	do
	{
		std::cout << "Number of elements to add: ";
		std::cin >> n;
		std::cin.get();
	} while (n < 0);

	std::cout << "Bottom range of elements: ";
	std::cin >> down;
	std::cin.get();

	std::cout << "Top range of elements: ";
	std::cin >> up;
	std::cin.get();

	addNRandomElementsToList(position, n, down, up);
}

void BidirectionalListManagement::addNRandomElementsToList(int position, int n, int rangeDown, int rangeUp)
{
	int val = 0;
	int weight = 0;
	double time = 0.0;
	double singleTime = 0.0;
	for (int i = 0; i < n; i++)
	{
		val = rand() % rangeUp + rangeDown;
		weight = rand() % 101;
		addNewElement(val, weight, position);
		appendDoubleToTextFile("list_add_times.txt", singleTime);
		time += singleTime;
	}

	std::cout << "[INFO] " << n << "elements has been added." << std::endl;
}

void BidirectionalListManagement::deleteAll()
{
	int choice = 0;
	int pos = 0;

	std::cout << "Choose type of deleting:\n" <<
		"1. From the end to beggining.\n" <<
		"2. From beggining to the end.\n" <<
		"3. From selected position to end, and then to beggining...\n";
	do
	{
		std::cout << "Your choice: ";
		std::cin >> choice;
		std::cin.get();
	} while (choice < 1 && choice > 3);

	if (choice == 1) pos = count - 1;
	else if (choice == 2) pos = 0;
	else
	{
		std::cout << "Insert position: ";
		std::cin >> pos;
		std::cin.get();
	}

	deleteAll(pos);
}

void BidirectionalListManagement::deleteAll(int position)
{
	int sizetemp = count;

	for (int i = 0; i < sizetemp; i++)
	{
		deleteElement(position);
		if (position > count - 1) position = count - 1;
	}
}

void BidirectionalListManagement::findElementTime()
{
	int val = 0;
	std::cout << "Value of element to find: ";
	std::cin >> val;
	std::cin.get();

	findElementTime(val);
}

void BidirectionalListManagement::findElementTime(int value)
{
	BidirectionalList* temp = getHead();
	double time = 0.0;
	for (int i = 0; i < count; i++)
	{
		if (temp->getValue() == value)
		{
			break;
		}
		temp = temp->getNext();
	}
}

bool BidirectionalListManagement::doesValueExist(int value)
{
	BidirectionalList* temp = getHead();
	while(temp)
	{
		if (temp->getValue() == value)
		{
			return true;
		}
		temp = temp->getNext();
	}
	return false;
}

int BidirectionalListManagement::getMinimumValueIndex(int value)
{
	if (count <= 0) return -1;

	BidirectionalList* temp = getHead()->getNext();
	int minimum = head->getValue();
	int i = 0;
	int index = 0;
	while(temp)
	{
		if(temp->getValue() < minimum)
		{
			index = i;
			minimum = temp->getValue();
		}
		i++;
		temp = temp->getNext();
	}

	return index;
}

BidirectionalList*& BidirectionalListManagement::operator[](int el)
{
	BidirectionalList* head = getHead();
	int i = 0;
	while (head && i < el)
	{
		head = head->getNext();
		i++;
	}
	return head;
}
