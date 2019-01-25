#ifndef GRILLE_HPP
#define GRILLE_HPP

#include <vector>

#include <cmath>


namespace dauphine
{
	class Grille {
	public:
		//Grille(double Time, double StockMax, double StockMin, double dt, double d_x);
		Grille(double Time, double Spot, double stddev, double dt, size_t NombrePas);
		std::vector<double> getStockVector() const;
		std::vector<double> getTimeVector() const;
		double getdt() const;
		size_t getTimeNumber() const;
		size_t GetTailleStock() const;
        double getSpot() const;
		std::vector<double> getdx() const;
		~Grille();

	private:
		double Time;
		double StockMax;
		size_t TimeNumber;
		size_t StockNumber;
		double dt;
        double Spot;
		std::vector<double> dx;
		std::vector<double> StockVector;
	};
}

#endif
