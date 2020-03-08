#include "Taxi.h"
#include "UI.h"

using namespace std;

UI::UI()
{
}


UI::~UI()
{
}

void UI::outputState(Taxi taxi)
{
	cout << taxi.getState();
}

void UI::showTaxiCount()
{
	cout << Taxi::taxiCount << " Taxis im Fuhrpark" << endl;
}

int UI::inputTaxi(std::vector<Taxi*> &taxiList)
{
	string input;

	int index;
	int inputInt;
	do
	{
		index = 1;
		inputInt = 0;
		cout << "Bitte waehlen Sie ihr Taxi:" << endl;
		for (vector<Taxi*>::iterator it = taxiList.begin(); it != taxiList.end(); ++it)
		{
			cout << index++ << ") " << (*it)->getName() << endl;
		}
		cout << index << ") exit" << endl;

		cin >> input;

		try {
			inputInt = stoi(input);
		}
		catch (invalid_argument) {
			errorInput();
			continue;
		}

		if (inputInt > index || inputInt == 0)
		{
			errorInput();
			continue;
		}
		else if(inputInt < index)
		{
			/*gibt korrekten Vector-Index zurueck*/
			return (inputInt-1);
		}
	} while (inputInt != index);

	return -1;
}

int UI::menuMain(Taxi taxi)
{
	string input;
	int inputInt;

	while (1)
	{
		cout << endl << "Menu fuer Taxi " << taxi.getName() << endl
			<< "1) Fahrt buchen mit Fahrgast" << endl
			<< "2) Fahrt buchen ohne Fahrgast" << endl
			<< "3) Tanken" << endl
			<< "4) Ausgabe der aktuellen Daten" << endl
			<< "5) Taxi wechseln" << endl
			<< "6) exit" << endl;
		cin >> input;

		try {
			inputInt = stoi(input);
		}
		catch (invalid_argument) {
			errorInput();
			continue;
		}

		if (0 < inputInt && inputInt < 7)
		{
			return inputInt;
		}
		errorInput();
	}

}

double UI::inputKm()
{
	float km;
	message("Bitte geben Sie die Strecke in km ein: ");
	cin >> km;
	return km;
}

double UI::inputGasprice()
{
	double price;
	cout << "Bitte geben Sie den Benzinpreis in Euro ein: ";
	cin >> price;
	if (price < 1.3 || price > 1.65)
	{
		error("Der Preis ist unplausibel und wird nicht akzeptiert!");
		return 0;
	}
	return price;
}

void UI::message(const string message)
{
	cout << endl << message << endl << endl;
}

void UI::errorInput()
{
	error("Ungueltige Eingabe, bitte waehlen Sie noch einmal!");
}

void UI::error(const string error)
{
	cerr << endl << error << endl << endl;
}
