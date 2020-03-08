// Aufgabe 05 - Taxi, Bjoern Oke Maas

#include "Route.h"
#include "Taxi.h"
#include "UI.h"
#include "Graph.h"
#include "NodeIdException.h"

using namespace std;

int Taxi::taxiCount = 0;	//Anzahl Taxis im Fuhrpark
int Taxi::taxiNumber = 1;	//fortlaufende Zahl fuer Nummerierung

/*
void createTaxi(double usage, double fare, double tankSize, string name, vector<Taxi*> &taxiList);
void createTaxi(double usage, double fare, double tankSize, vector<Taxi*> &taxiList);
Taxi copyTaxi(Taxi taxi);
bool isCopy(Taxi origTaxi, Taxi copiedTaxi);
void test(vector<Taxi*> &taxiList);
Node* createNode(string name);
*/

deque<Edge*> rPath;
int i;
size_t* idx = 0;

int main()
{
	/***
	Graph, nodes und edges werden erstellt
	alle nodes und edges in den Graphen eingefügt 
	***/

	Graph* graph = new Graph();
	string init[10][3] = {
		{"Alexanderplatz", "Funkturm", "10.2"},
		{"Funkturm", "Strandbad Wannsee", "11.2"},
		{"Strandbad Wannsee", "Brandenburger Tor", "18"},
		{"Brandenburger Tor", "Alexanderplatz", "2.3"},
		{"Alexanderplatz", "Ostkreuz", "6.2"},
		{"Ostkreuz", "Regattastrecke Gruenau", "14.6"},
		{"Regattastrecke Gruenau", "Grenzallee", "12.8"},
		{"Grenzallee", "Alexanderplatz", "11.2"},
		{"Grenzallee", "Funkturm", "14.9"},
		{"Funkturm", "Zitadelle Spandau", "8.5"},
	};

	cout << "************************* Graph wird initialisiert *************************\n\n";
	for(i=0; i<10; i++)
	{ 
		Node* ptrSrc = graph->findNode(init[i][0]);
		if (ptrSrc == NULL)
		{
			ptrSrc = new Node(init[i][0]);
		}

		Node* ptrDst = graph->findNode(init[i][1]);
		if (ptrDst == NULL)
		{
			ptrDst = new Node(init[i][1]);
		}

		Route* ptrRt = new Route(*ptrSrc, *ptrDst, stof(init[i][2], idx));

		graph->addEdge(ptrRt);
	}

	/***
	Der optimale Weg von Funkturm nach Alexanderplatz soll gesucht werden
	***/

	Node* start = graph->findNode("Funkturm");
	Node* ziel = graph->findNode("Alexanderplatz");
	cout << "*********** Suche optimalen Weg von " << start->getID() 
		<< " nach " << ziel->getID() << " ***********\n\n";

	graph->findShortestPathDijkstra(rPath, *start, *ziel);

	/***
	Das Ergebnis von findShortestPathDijkstra() wird ausgegeben
	***/

	if (rPath.empty())
		{
			cout << "--- Es gibt keinen Weg! ---\n";
		}
		else
		{
			cout << endl << "Entfernung " << start->getID() << " nach " << ziel->getID() 
				<< ": " << rPath.back()->getDstNode().getDist() << "\n";
			cout << "Optimale Route:\n";
			while (!rPath.empty())
			{
				cout << (rPath.front()->toString()) << endl;
				rPath.pop_front();
			}
		}

	/***
	Erst wird gezielt eine node geloescht, dann der ganze Graph
	***/

	cout << endl << "************ node Alexanderplatz wird aus dem Graphen entfernt ************\n\n";

	graph->remove(*ziel);

	cout << endl << "*************************** Graph wird geloescht **************************\n\n";
	delete graph;


	/*
	try
	{
		edge2 = new Edge("Bremen", "Bonn");
	}
	catch (NodeIdException& ex)
	{
		cout << ex.getError() << endl;
	}
	*/

	/*
	vector<Taxi*> taxiList;
	test(taxiList);
	double gasPrice;
	int choice;

	// inputTaxi() gibt den Vector-Index des gewaehlten Taxis zurueck, oder -1 bei exit
	int currentTaxi = UI::inputTaxi(taxiList);

	while(currentTaxi != -1)
	{
		choice = UI::menuMain(*taxiList[currentTaxi]);

		switch (choice)
		{
			case 1:	//Fahrt buchen mit Fahrgast
				taxiList[currentTaxi]->bookTrip(UI::inputKm(), true);
				break;

			case 2:	//Fahrt buchen ohne Fahrgast
				taxiList[currentTaxi]->bookTrip(UI::inputKm(), false);
				break;

			case 3:	//Tanken
				gasPrice = UI::inputGasprice();
				taxiList[currentTaxi]->fillUp(gasPrice);
				break;

			case 4:	//Ausgabe der aktuellen Daten
				UI::outputState(*taxiList[currentTaxi]);
				break;

			case 5:	//Taxi wechseln
				currentTaxi = UI::inputTaxi(taxiList);
				break;

			case 6:	//exit
				currentTaxi = -1;
				break;
		}
	}

	for (unsigned int i = 0; i < taxiList.size(); i++)
	{
		delete taxiList[i];
	}
	*/


	return 0;
}

Node* createNode(string name)
{
	try
	{
		return new Node(name);
	}
	catch (NodeIdException& ex)
	{
		cout << ex.getError() << endl;
	}
	return new Node();
}

/****
Hilfsfunktionen fuer die Tests
****/
void createTaxi(double usage, double fare, double tankSize, string name, vector<Taxi*> &taxiList)
{
	Taxi* taxiptr = new Taxi(usage, fare, tankSize, name);
	taxiList.push_back(taxiptr);
	cout << "Taxi erstellt mit Namen: " << taxiptr->getName() << endl;
}

void createTaxi(double usage, double fare, double tankSize, vector<Taxi*> &taxiList)
{
	Taxi* taxiptr = new Taxi(usage, fare, tankSize);
	taxiList.push_back(taxiptr);
	cout << "Taxi erstellt ohne Namen: " << taxiptr->getName() << endl;
}

Taxi copyTaxi(Taxi taxi)
{
	Taxi copiedTaxi = taxi;
	cout << "Taxi " << taxi.getName() << " wurde kopiert" << endl;
	return copiedTaxi;

}

bool isCopy(Taxi origTaxi, Taxi copiedTaxi)
{
	if (origTaxi.getCash() == copiedTaxi.getCash() && origTaxi.getFare() == copiedTaxi.getFare()
		&& origTaxi.getName() == copiedTaxi.getName() && origTaxi.getTacho() == copiedTaxi.getTacho()
		&& origTaxi.getTank() == copiedTaxi.getTank() && origTaxi.getTankSize() == copiedTaxi.getTankSize()
		&& origTaxi.getUsage() == copiedTaxi.getUsage())
	{
		return true;
	}
	return false;
}

/*
void test(vector<Taxi*> &taxiList)
{
	cout << "***** Test Start *****" << endl << endl;

	createTaxi(7.2, 0.7, 75, "B-MH1800", taxiList);
	createTaxi(12.5, 0.95, 90, "B-CT222", taxiList);
	createTaxi(12.5, 0.6, 70, taxiList);

	UI::showTaxiCount();
	cout << "Taxi " << taxiList[2]->getName() << " wurde geloescht!" << endl;
	delete taxiList[2];
	taxiList.erase(taxiList.begin() + 2);
	UI::showTaxiCount();
	createTaxi(12.5, 0.6, 70, taxiList);
	UI::showTaxiCount();

	Taxi taxi3 = copyTaxi(*taxiList[0]);
	UI::showTaxiCount();
	cout << "Kopie ist Kopie: " << isCopy(*taxiList[0], taxi3) << endl;
	cout << "Kopie von " << taxi3.getName() << " wird geloescht" << endl;
	taxi3.~Taxi();
	UI::showTaxiCount();

	taxiList[0]->bookTrip(20, true);
	UI::outputState(*taxiList[0]);
	taxiList[0]->bookTrip(2000, true);

	taxiList[0]->bookTrip(20, true);
	UI::outputState(*taxiList[0]);

	taxiList[0]->bookTrip(30, false);
	UI::outputState(*taxiList[0]);

	taxiList[1]->bookTrip(50, false);
	UI::outputState(*taxiList[1]);

	taxiList[0]->fillUp(1.46);
	UI::outputState(*taxiList[0]);

	taxiList[1]->fillUp(1.61);
	UI::outputState(*taxiList[1]);
	cout << endl << "***** Test Ende *****" << endl << endl;
}
*/
