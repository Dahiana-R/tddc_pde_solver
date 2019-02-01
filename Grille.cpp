#include "Grille.hpp"
#include <vector>
#include <cmath>

namespace dauphine
{
	Grille::Grille(double Time, double Spot, double stddev, double dt, size_t NombrePas)
		: Time(Time), TimeNumber(floor((Time - 0) / dt) + 1), dt(dt), Spot(Spot)
	{

		double center = log(Spot);
		StockMax = (log(Spot) + 5 * stddev*sqrt(Time));
		double StockMin = (log(Spot) - 5 * stddev*sqrt(Time));

		//On regle le probleme des valeurs impaires, c'est tres mal fait; a changer.
		if (NombrePas % 2 == 0) {
			StockNumber = NombrePas;
		}
		else {
			StockNumber = NombrePas + 1;
		}

		double dx_step = (StockMax - StockMin) / NombrePas;
		
        std::vector<double> stock_vect(StockNumber);

		//On peut combiner les deux boucles, je me suis pris la tete.

		for (std::size_t i = 0; i < StockNumber ; ++i)
		{
			//on fait une exception de facon a avoir pile le spot et pas un arrondi du style 100.0000000001
			if (i == StockNumber / 2 - 1) {
				stock_vect[i] = Spot;
			}
			else {
				stock_vect[i] = log(Spot) + (i - floor(StockNumber / 2) + 1 )* dx_step;
				stock_vect[i] = exp(stock_vect[i]);
			}
		}

		std::vector<double> dx_vect(StockNumber - 1);
        std::fill(dx_vect.begin(), dx_vect.end(), dx_step);
        
		dx = dx_vect;
		StockVector = stock_vect;

	}

	Grille::~Grille() {

	}
	double Grille::getdt() const{
		return dt;
	}
    double Grille::getSpot() const {
        return Spot;
    }
    // Since the grid is uniform, no need to store N times
    // the same value of dx, just store a double
	std::vector<double> Grille::getdx() const{
		return dx;
	}
    
    // No need to store a StockNumber data member,
    // simply return StockVector.size()
	size_t Grille :: GetTailleStock() const{
		return StockNumber;
	}

    // Same remark, could return TimeVector.size()
    // (but this implies storing the TimeVector
    // instead of building it upon each call)
	size_t Grille::getTimeNumber() const {
		return TimeNumber;
	}
    
    // SHould be returned by const ref
	std::vector<double> Grille::getStockVector() const{

		return StockVector;
	}

    // TimeVector should be stored as a data member,
    // and this method should return it by const ref
	std::vector<double> Grille::getTimeVector() const{
		std::vector<double> dt_vect(TimeNumber);

		for (size_t i = 0; i < TimeNumber; i++) {
			dt_vect[i] = 0 + i * dt;
		}                                                                                                                                                                                        
		return dt_vect;
	}

}
