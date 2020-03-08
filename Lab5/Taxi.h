#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>

class Taxi
{
public:
	static int taxiCount;	//Anzahl Taxis im Fuhrpark
	static int taxiNumber;	//fortlaufende Zahl fuer Nummerierung

	Taxi();
	~Taxi();
	Taxi(const double usage, const double fare, const double tankSize);
	Taxi(const double usage, const double fare, const double tankSize, std::string name);
	Taxi(const Taxi& taxi);

	std::string getName() const;
	int setName(std::string name);
	double getTacho() const;
	double getTank() const;
	double getCash() const;
	double getTankSize() const;
	double getUsage() const;
	double getFare() const;
	std::string getState() const;
	std::string getDefaultName() const;

	void bookTrip(double km, bool passenger);
	void fillUp(double gasPrice);
	void addTacho(double km);
	void addTank(double liter);
	void subtractTank(double liter);
	void addCash(double money);
	void subtractCash(double money);
	bool isGasEnough(double km) const;
	double calculateUsedLiter(double km) const;
	double calculateFarePrice(double km) const;

private:
	double tacho;			//Tageskilometerstand (km)
	double tank;				//aktueller Tankinhalt (Liter)
	double cash;				//Geldbilanz (Euro)
	const double tankSize;	//maximaler Tankinhalt (Liter)
	const double usage;		//Verbrauch pro km (Liter)
	const double fare;		//Fahrpreis pro km (Euro)
	std::string name;		//Taxiname
};

