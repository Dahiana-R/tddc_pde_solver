#include "Grille.hpp"
#include <vector>

namespace dauphine
{
/*	 Grille::Grille(double Time, double StockMax, double TimeNumber, double StockNumber)
		: Time(Time), StockMax(StockMax), TimeNumber(TimeNumber),StockNumber(StockNumber),dt(((Time - 0) / TimeNumber)),dx(((StockMax - 0) / StockNumber))
	{
		std::vector<double> test(StockNumber);

		for (int i = 0; i < StockNumber; i++) {
			test[i] = 0 + i * dx;
		}
		StockVector = test;
	}*/

	Grille::Grille(double Time, double StockMax, double StockMin, double dt, double dx)
		: Time(Time), StockMax(StockMax), TimeNumber(floor((Time-0)/dt) +1), StockNumber(floor((StockMax - StockMin) / dx) + 1), dt(dt), dx(dx)
	{

		std::vector<double> test(StockNumber);
		for (std::size_t i = 0; i < StockNumber; ++i)
		{
			test[i] = 0 + i * dx;
		}
		StockVector = test;
	}

	Grille::~Grille() {

	}
	double Grille::getdt() const{
		return dt;
	}
	double Grille::getdx() const{
		return dx;
	}
	double Grille :: GetTailleStock() const{
		return StockNumber;
	}
	double Grille::getTimeNumber() const {
		return TimeNumber;
	}

	std::vector<double> Grille::getStockVector() const{

		return StockVector;
	}
	std::vector<double> Grille::getTimeVector() const{
		std::vector<double> test(TimeNumber);

		for (int i = 0; i < TimeNumber; i++) {
			test[i] = 0 + i * dt;
		}
		return test;
	}

}