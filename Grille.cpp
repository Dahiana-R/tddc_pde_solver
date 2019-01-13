#include "Grille.hpp"
#include <vector>
#include <cmath>

namespace dauphine
{
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

	Grille::Grille(double Time, double Spot, double stddev, double dt, size_t NombrePas, double useless)
		: Time(Time), TimeNumber(floor((Time - 0) / dt) + 1), dt(dt)
	{

		double center = log(Spot);
		StockMax = (log(Spot) + 5 * stddev*sqrt(Time));
		double StockMin= (log(Spot) - 5 * stddev*sqrt(Time));

		//On règle le problème des valeurs impaires, c'est très mal fait; à changer.
		if (NombrePas % 2 == 0) {
			StockNumber = NombrePas;
		}
		else {
			StockNumber = NombrePas + 1;
		}

		double dx_test = (StockMax - StockMin) / NombrePas;
		std::vector<double> test(StockNumber);

		//On peut combiner les deux boucles, je me suis pris la tete.
		for (int i = 0; i < StockNumber / 2 - 1; ++i)
		{
			test[i] = center + (i - floor(StockNumber / 2) + 1) * dx_test;
			test[i] = exp(test[i]);
		}

		for (std::size_t i = 0; i < StockNumber/2 + 1; ++i)
		{
			//on fait une exception de facon a avoir pile le spot et pas un arrondi du style 100.0000000001
			if (i == 0) {
				test[i + StockNumber / 2 - 1] = Spot;
			}
			else {
				test[i + StockNumber / 2 - 1] = log(Spot) + i * dx_test;
				test[i + StockNumber / 2 - 1] = exp(test[i + StockNumber / 2 - 1]);
			}
		}


		std::vector<double> test2(StockNumber - 1);

		for (std::size_t i = 0; i < StockNumber -1 ; ++i)
		{
			test2[i] = dx_test;
		}
		dx = test2;
		StockVector = test;

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
