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

	this->time = TimeCounter();
}

Menu::Menu(bool directed)
{
	this->graph = Graph(directed);
}


Menu::~Menu(){}

void Menu::menu()
{
	int choice1 = 0;
	int choices = 8;

	do
	{
		std::cout << "===== MENU =====" << std::endl;
		std::cout << "1. Pokaz reprezentacje grafu" << std::endl;
		std::cout << "2. Wypelnij graf z pliku" << std::endl;
		std::cout << "3. Wypenij graf losowo" << std::endl;
		std::cout << "4. Algorytm Dijkstry" << std::endl;
		std::cout << "5. Algorytm Prima" << std::endl;
		std::cout << "6. Edytuj graf" << std::endl;
		std::cout << "7. TESTOWANIE" << std::endl;
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
			editMenu();
			break;
		case 7:
			//TODO
			break;
		default:
			break;
		}
	} while (choice1 != choices);
}

void Menu::editMenu()
{
	int choice1 = 0;
	int choices = 5;

	do
	{
		std::cout << "=====  MENU EDYCJI =====" << std::endl;
		std::cout << "1. Dodaj wierzcholek" << std::endl;
		std::cout << "2. Dodaj krawedz" << std::endl;
		std::cout << "3. Edytuj wage krawedzi" << std::endl;
		std::cout << "4. Zmien typ grafu (skierowany/nieskierowany)" << std::endl;
		std::cout << choices << ". Cofnij" << std::endl;

		do
		{
			std::cout << "Twoj wybor: ";
			std::cin >> choice1;
			std::cin.get();
		} while (choice1 < 1 || choice1 > choices);

		int to = 0, from = 0, weight = 0;

		switch (choice1)
		{
		case 1:
			graph.addVertex();
			std::cout << "Dodano wierzcholek na pozycje: " << graph.getVertices() - 1 << std::endl;
			if (graph.getVertices() > 1)
			{
				std::cout << "Polacz nowo dodany wierzcholek z istniejacym grafem." << std::endl;
				std::cout << "Podaj dane krawedzi tak aby jeden jej koniec byl polaczony z nowym wierzcholkiem (indeks =" << graph.getVertices() - 1 << ")" << std::endl;
				do
				{
					std::cout << "Podaj indeks wierzcholka poczatkowego krawedzi: ";
					std::cin >> from;
					std::cin.get();

					std::cout << "Podaj indeks wierzcholka koncowego krawedzi: ";
					std::cin >> to;
					std::cin.get();
					//ask until:
						//indexes are correct
						//one of indexes is last index
						//both aren't the same
				} while (from < 0 || from > graph.getVertices() - 1 || to < 0 || to > graph.getVertices() - 1 ||
						(to != graph.getVertices() - 1 && from != graph.getVertices() - 1) || to == from);
				do
				{
					std::cout << "Podaj wage krawedzi: ";
					std::cin >> weight;
					std::cin.get();
				} while (weight <= 0 || weight >= 1000);

				graph.addEdge(from, to, weight);
			}
			break;
		case 2:
			graph.addEdge();
			break;
		case 3:
			do
			{
				std::cout << "Podaj indeks wierzcholka poczatkowego krawedzi: ";
				std::cin >> from;
				std::cin.get();

				std::cout << "Podaj indeks wierzcholka koncowego krawedzi: ";
				std::cin >> to;
				std::cin.get();
				//ask until:
				//indexes are correct
				//one of indexes is last index
				//both aren't the same
			} while (from < 0 || from > graph.getVertices() - 1 || to < 0 || to > graph.getVertices() - 1 || to == from);
			do
			{
				std::cout << "Podaj nowa wage krawedzi: ";
				std::cin >> weight;
				std::cin.get();
			} while (weight <= 0 || weight >= 1000);

			graph.editEdge(from,to,weight);

			break;
		case 4:
			this->graph = Graph(!graph.isDirected());
			std::cout << "Zmieniono formê grafu na " << (graph.isDirected() ? "skierowany" : "nieskierowany") << std::endl;
			break;
		default:
			break;
		}
	} while (choice1 != choices);
}
