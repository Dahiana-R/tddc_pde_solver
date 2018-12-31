#include "Grille.hpp"
#include <vector>

namespace dauphine
{
	Grille::Grille(double Time, double StockMax, double TimeNumber, double StockNumber)
		: Time(Time), StockMax(StockMax), TimeNumber(TimeNumber),StockNumber(StockNumber),dt((Time - 0 / StockNumber)),dx((StockMax - 0) / StockNumber)
	{

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
		std::vector<double> test(StockNumber + 1);
		
		for (int i = 0; i < StockNumber + 1; i++) {
			test[i] = 0 + i * dx;
		}
		return test;
	}
	std::vector<double> Grille::getTimeVector() const{
		std::vector<double> test(TimeNumber +1);
		double step = (Time - 0) / dt;
		for (int i = 0; i < TimeNumber + 1; i++) {
			test[i] = 0 + i * dt;
		}
		return test;
	}

}