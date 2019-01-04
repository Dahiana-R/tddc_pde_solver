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
		return std::max(x-100., 0.);
	}

	void essai() {
		Parameters param(0.2, 0., 0.5);
		Grille mesh(1, 300, 20, (1. / 252.) , 1);
		Boundaries bound(mesh, param, payoff);
		std::vector<double> price = dauphine::CrankNicholson(mesh, param, bound);
		std::vector<double> payoff = bound.getpayoff();
		std::vector<double> stock = mesh.getStockVector();
		price.push_back(bound.getupercondition()[mesh.getTimeNumber() - 1]);
		price.insert(price.begin(), bound.getlowercondition()[0]);

		for (std::size_t i = 0; i < price.size(); i++)
		{
			std::cout << stock[i] << " : " << price[i] << std::endl;
		}
		//std::cout << stock[199] << " : " << price[199] << std::endl;
	}

	/*void essai2() {
		Parameters param(0.2, 0.01, 0.5);
		Grille mesh(0.5, 200, 0, (1. / 252.) , 0.0001);
		Boundaries bound(mesh, param, payoff);
		std::vector<double> d = { 1,2,3 };
		std::vector<double> a = { 1,2,3 };
		std::vector<double> vector = dauphine::vectorpayoff(bound);
		
		//paramètre de gauche(avec Theta)
		double aleft = Lower_diag_coeff(mesh, param, false);
		double bleft = Mid_diag_coeff(mesh, param, false);
		double cleft = Upper_diag_coeff(mesh, param, false);
		//paramètre de droite(donc Theta-1)
		double aright = Lower_diag_coeff(mesh, param, true);
		double bright = Mid_diag_coeff(mesh, param, true);
		double cright = Upper_diag_coeff(mesh, param, true);

		//vecteur contenant tous les coef, on les calcule une fois on est tranquille, penser à changer sur les autres fonctions si je ne l'ai pas fait.
		std::vector<double>coefficients { aleft,bleft,cleft,aright,bright,cright };
		std::vector<double> price = dauphine::rightvector(mesh, param, vector, bound, coefficients, 0);
		std::vector<double> upper = bound.getupercondition();
		for (std::size_t i = 0; i < coefficients.size(); ++i)
		{
			std::cout << coefficients[i] << " : " << price[i] << std::endl;
		}
		/*for (std::size_t i = 0; i < price.size(); ++i)
		{
			std::cout << i << " : " << price[i] << std::endl;
		}
		for (std::size_t i = 0; i < upper.size(); ++i)
		{
			std::cout << i << " : " << upper[i] << std::endl;
		}

	}*/
	void essai3() {
		Parameters param(0.2, 0.01, 0.5);
		Grille mesh(0.5, 200, 0, (1. / 252.), 0.0001);
		Boundaries bound(mesh, param, payoff);
	}

}

int main(int argc, char* argv[])
{
	double spot = 100;
	double strike = 100;
	double volatility = 0.2;
	double maturity = 2;
	bool istrue = true;

	std::cout << "BS Price is:"<< dauphine::bs_price(spot, strike, volatility, maturity, istrue) << std::endl;

	std::cout << "Nicholson Crank:" << std::endl;	
	dauphine::essai();

    return 0;
}
