#include "Menu.h"



Menu::Menu()
{
	Matrix matrix;
	this->matrixRepresentation = matrix;

	//TODO
	//List represenation when class is ready
}


Menu::~Menu()
{
}

void Menu::showMenu()
{
	//variable for user's choice
	int choice = -1;
	
	do
	{
		//Minimal spanning tree
		std::cout << "1. Minimalne drzewo rozpinajace ..." << std::endl;
		//Finding the shortest path in tree
		std::cout << "2. Znajdowanie nakrotszej sciezki ..." << std::endl;
		std::cout << "3. Zamknij program" << std::endl;
	} while (choice < 0 || choice > 3);
	
	switch (choice)
	{
	case 1:
		minimalSpanningTree();
		break;
	case 2:
		//shortestPath
		break;
	case 3:
		return;
	default:
		break;
	}
}

void Menu::minimalSpanningTree()
{
	//variable for user's choice
	int choice = -1;
	int choices = 3;
	do
	{
		//Minimal spanning tree
		std::cout << "1. Pokaz graf (macierzowo i listowo) ..." << std::endl;
		//Finding the shortest path in tree
		std::cout << "2. Wypelnij graf losowymi danymi ..." << std::endl;
		std::cout << "3. Wypelnij graf z pliku ..." << std::endl;
		std::cout << "4. Algorytm Prima ..." << std::endl;
		std::cout << "5. Algrotym Kruskala ..." << std::endl;
		std::cout << choices << ". Wroc" << std::endl;
	} while (choice < 0 || choice > choices);

	switch (choice)
	{
	case 1:
		minimalSpanningTree();
		break;
	default:
		return;
		break;
	}
}

/*
void Menu::matrixMenu()
{
	

	//variable for user's choice
	int choice = -1;
	//number of possible choices in matrix menu
	int matrixChoices = 6;

	std::cout << "1. Pokaz macierz" << std::endl;
	std::cout << "2. Dodaj wierzcholki ..." << std::endl;
	std::cout << "3. Usun wierzcholek ..." << std::endl;
	std::cout << "4. Dodaj krawedz ..." << std::endl;
	std::cout << "5. Usun  krawedz ..." << std::endl;
	//always last possible choice on list
	std::cout << matrixChoices << ". Cofnij" << std::endl;

	do
	{
		std::cout << "Twoj wybor: ";
		std::cin >> choice;
		std::cin.get();

	} while (choice < 0 || choice > matrixChoices);


	switch (choice)
	{
	case 1:
		matrixRepresentation.showMatrix();
		break;
	case 2:
		matrixRepresentation.addNNewVertex();
		break;
	case 3:
		matrixRepresentation.removeVertex();
		break;
	case 4:
		matrixRepresentation.addEdge();
		break;
	case 5:
		matrixRepresentation.removeEdge();
	case 6:
		//TO DO
	default:
		std::cout << "Zly wybor;" << std::endl;
		break;
	}
	
}
*/
