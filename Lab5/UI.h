#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

class UI
{
public:
	UI();
	~UI();
	static void outputState(Taxi taxi);
	static int inputTaxi(std::vector<Taxi*> &taxilist);
	static int menuMain(Taxi taxi);
	static void errorInput();
	static double inputKm();
	static double inputGasprice();
	static void error(const std::string error);
	static void message(const std::string message);
	static void showTaxiCount();
};
