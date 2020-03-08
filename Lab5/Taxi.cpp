
#include "Taxi.h"
#include "UI.h"

using namespace std;

Taxi::Taxi()
	: usage(0), fare(0), tankSize(0), tacho(0), tank(0), cash(0)
{
	taxiCount++;
	taxiNumber++;
	this->setName(getDefaultName());
}

Taxi::~Taxi()
{
	taxiCount--;
}

Taxi::Taxi(const double usage, const double fare, const double tankSize)
	:usage(usage), fare(fare), tankSize(tankSize), tacho(0), tank(tankSize), cash(0)
{
	this->setName(getDefaultName());
	taxiCount++;
	taxiNumber++;
}

Taxi::Taxi(const double usage, const double fare, const double tankSize, string name)
	: usage(usage), fare(fare), tankSize(tankSize), tacho(0), tank(tankSize), cash(0)
{
	if (this->setName(name) != 0)
	{
		this->setName(getDefaultName());
	}
	taxiCount++;
	taxiNumber++;
}

Taxi::Taxi(const Taxi& taxi)
	: usage(taxi.usage), fare(taxi.fare), tankSize(taxi.tankSize),
	tacho(taxi.tacho), tank(taxi.tank), cash(taxi.cash), name(taxi.name)
{
	taxiCount++;
	taxiNumber++;
}

string Taxi::getDefaultName() const
{
	stringstream stream;
	stream << "Taxi_" << setw(3) << setfill('0') << right << taxiNumber;
	return stream.str();
}

string Taxi::getName() const
{
	return(this->name);
}

int Taxi::setName(string name)
{
	if (name.length() > 8)
	{
		UI::error("Der Name ist zu lang!");
		return 1;
	}
	else
	{
		this->name = name;
		return 0;
	}
}

double Taxi::getTacho() const
{
	return(this->tacho);
}

double Taxi::getTank() const
{
	return(this->tank);
}

double Taxi::getCash() const
{
	return(this->cash);
}

double Taxi::getTankSize() const
{
	return(this->tankSize);
}

double Taxi::getUsage() const
{
	return(this->usage);
}

double Taxi::getFare() const
{
	return(this->fare);
}

void Taxi::addTacho(double km)
{
	this->tacho += km;
}

void Taxi::addTank(double liter)
{
	this->tank += liter;
}

void Taxi::subtractTank(double liter)
{
	this->tank -= liter;
}

void Taxi::addCash(double money)
{
	this->cash += money;
}

void Taxi::subtractCash(double money)
{
	this->cash -= money;
}

double Taxi::calculateFarePrice(double km) const
{
	return (km * this->fare);
}

bool Taxi::isGasEnough(double km) const
{
	return (calculateUsedLiter(km) <= (this->tank));
}

double Taxi::calculateUsedLiter(double km) const
{
	return (km * this->usage / 100);
}

/*
Tanken: voll oder so viel wie Geld erlaubt
Eingabe: Benzinpreis
*/
void Taxi::fillUp(double gasPrice)
{
	if (gasPrice != 0)
	{
		double affordableGas = (this->cash / gasPrice);
		double wantedGas = this->tankSize - this->tank;

		if (wantedGas == 0)
		{
			UI::error("Der Tank ist bereits voll!");
		}

		else if (wantedGas <= affordableGas)
		{
			this->tank = this->tankSize;
			subtractCash(wantedGas * gasPrice);
			UI::message("Vollgetankt!");
		}
		else
		{
			addTank(affordableGas);
			this->cash = 0;
			cout << endl << affordableGas << " Liter getankt." << endl << endl;
		}
	}
}

/*
Buchen einer Fahrt:
Eingabe: Kilometer km, Fahrgast true/false
*/
void Taxi::bookTrip(double km, bool passenger)
{
	if (!isGasEnough(km))
	{
		UI::error("Fahrt nicht moeglich, zu wenig Benzin im Tank!");
	}
	else
	{
		addTacho(km);
		subtractTank(calculateUsedLiter(km));
		if (passenger)
		{
			addCash(calculateFarePrice(km));
		}
		UI::message("Fahrt gebucht!");
	}
}

/*
Ausgabe aktueller Daten des Taxis
*/
string Taxi::getState() const
{
	stringstream stream;
	stream << fixed << setprecision(2)
		<< setw(9) << left << name << " >> "
		<< setw(7) << right << tacho << " km, "
		<< setw(7) << right << tank << " l, "
		<< setw(7) << right << cash << " Euro" << endl;
	return stream.str();
}
