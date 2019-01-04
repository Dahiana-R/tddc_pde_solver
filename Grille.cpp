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

	Grille::Grille(double Time, double StockMax, double StockMin, double dt, double d_x)
		: Time(Time), StockMax(StockMax), TimeNumber(floor((Time-0)/dt) +1), StockNumber(floor((StockMax - StockMin) / d_x) + 1), dt(dt)
	{

		std::vector<double> test(StockNumber);
		for (std::size_t i = 0; i < StockNumber; ++i)
		{
			test[i] = StockMin + i * d_x;
		}
		StockVector = test;
		std::vector<double> test2(StockNumber-1);
		for (std::size_t i = 0; i < StockNumber-1; ++i)
		{
			test2[i] = log(StockVector[i+1])-log(StockVector[i]);
		}
		dx = test2;
	}

	Grille::~Grille() {

	}
	double Grille::getdt() const{
		return dt;
	}
	std::vector<double> Grille::getdx() const{
		return dx;
	}
	size_t Grille :: GetTailleStock() const{
		return StockNumber;
	}
	size_t Grille::getTimeNumber() const {
		return TimeNumber;
	}

	std::vector<double> Grille::getStockVector() const{

		return StockVector;
	}
	std::vector<double> Grille::getTimeVector() const{
		std::vector<double> test(TimeNumber);

		for (size_t i = 0; i < TimeNumber; i++) {
			test[i] = 0 + i * dt;
		}
		return test;
	}

}