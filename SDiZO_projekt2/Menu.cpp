#include "Menu.h"



Menu::Menu()
{
	int choice = 0;
	std::cout << "Wybierz forme grafu:" << std::endl;
	std::cout << "1. Skierowany" << std::endl;
	std::cout << "2. Nieskierowany" << std::endl;

	do
	{
		std::cin >> choice;
		std::cin.get();
	} while (choice < 1 || choice > 2);

	if (choice == 1)
	{
		Graph g(true);
		this->graph = g;
	}
	else
	{
		Graph g(false);
		this->graph = g;
	}
}

Menu::Menu(bool directed)
{
	this->graph = Graph(directed);
}


Menu::~Menu(){}

void Menu::menu()
{
	int choice1 = 0;
	int choices = 7;

	do
	{
		std::cout << "===== MENU =====" << std::endl;
		std::cout << "1. Pokaz reprezentacje grafu" << std::endl;
		std::cout << "2. Wypelnij graf z pliku" << std::endl;
		std::cout << "3. Wypenij graf losowo" << std::endl;
		std::cout << "4. Algorytm Dijkstry" << std::endl;
		std::cout << "5. Algorytm Prima" << std::endl;
		std::cout << "6. Zmien forme grafu" << std::endl;
		std::cout << choices << ". Wyjdz" << std::endl;

		do
		{
			std::cout << "Twoj wybor: ";
			std::cin >> choice1;
			std::cin.get();
		} while (choice1 < 1 || choice1 > choices);

		switch (choice1)
		{
		case 1:
			std::cout << "======================================" << std::endl;
			std::cout << "Wybrana forma grafu: " << (graph.isDirected() ? "SKIEROWANY" : "NIESKIEROWANY") << std::endl;
			graph.showRepresentations();
			break;
		case 2:
			graph.fillFromFile();
			break;
		case 3:
			graph.fillRandom();
			break;
		case 4:
			graph.dijkstra();
			break;
		case 5:
			graph.prim();
			break;
		case 6:
			this->graph = Graph(!graph.isDirected());
			std::cout << "Zmieniono formê grafu na " << (graph.isDirected() ? "skierowany" : "nieskierowany") << std::endl;
			break;
		default:
			break;
		}
	} while (choice1 != choices);
}