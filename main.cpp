#include <iostream>
#include <algorithm>
#include <cmath>
#include <limits>
#include "closed_form.hpp"
#include "Solver.hpp"
#include "Parameters.hpp"
#include "Grille.hpp"
#include "Boundaries.hpp"

namespace dauphine {
	double payoff(double x) {
		return std::max(x, 100.);
	}

	/*void essai() {
		//Grille mesh(1, 200, 250, 201);
		Parameters param(0.2, 0.01, 0.5);
		Boundaries bound(mesh, param, payoff);
		std::vector<double> price = dauphine::CrankNicholson(mesh, param, bound, payoff);
		for (std::size_t i = 0; i < price.size(); ++i)
		{
			std::cout << i << " : " << price[i] << std::endl;
		}
	}*/

	void essai2() {
		Parameters param(0.2, 0.01, 0.5);
		//Grille mesh(1, 200, 250, 201);
		Grille mesh(1, 200, 0, (1. / 252.) , 2);
		std::cout << param.GetRate() << std::endl;
		std::cout << param.GetVol() << std::endl;
		std::vector<double> price = mesh.getStockVector();
		for (std::size_t i = 0; i < price.size(); ++i)
		{
			std::cout << i << " : " << price[i] << std::endl;
		}

	}

}

int main(int argc, char* argv[])
{
	double spot = 100;
	double strike = 100;
	double volatility = 0.2;
	double maturity = 1;
	bool istrue = true;

	std::cout << "BS Price is:"<< dauphine::bs_price(spot, strike, volatility, maturity, istrue) << std::endl;

	std::cout << "Nicholson Crank:" << std::endl;	
	dauphine::essai2();

    return 0;
}
