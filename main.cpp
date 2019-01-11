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

	std::vector<double> essai(double spot) {
		Parameters param(0.2, 0., 0.5);
		//Grille mesh(1., 200, 20, (1. / 252.) , 0.5);
		//test pour un dx fixé en prenant comme frontiere spot +- 5stddev racine T. On centre sur le spot.
		Grille mesh(1., 100., 0.2, (1. / 252.), 100, 0.2);
		Boundaries bound(mesh, param, payoff);
		//test
		std::vector<double> avantdernier(mesh.getTimeNumber());
		//
		std::vector<double> price = dauphine::CrankNicholson(mesh, param, bound, avantdernier);
		std::vector<double> payoff = bound.getpayoff();
		std::vector<double> stock = mesh.getStockVector();
		price.push_back(bound.getupercondition()[mesh.getTimeNumber() - 1]);
		price.insert(price.begin(), bound.getlowercondition()[mesh.getTimeNumber() - 1]);

		//test
		avantdernier.push_back(bound.getupercondition()[mesh.getTimeNumber() - 2]);
		avantdernier.insert(avantdernier.begin(), bound.getlowercondition()[mesh.getTimeNumber() - 2]);
		//test avec adresse

		
		std::vector<double> solution(4);
		//on cherche l'index pour lequel on veut le prix
		auto iter = std::find(stock.begin(), stock.end(), spot);
		size_t index = std::distance(stock.begin(), iter);
		//on le met dans un vecteur
		solution[0]= price[index];
		solution[1] = (price[index + 1] - price[index - 1]) / (stock[index + 1] - stock[index - 1]);
		solution[2] = (price[index + 1] - 2*price[index] + price[index - 1]) / (pow((stock[index + 1] - stock[index]),2));
		solution[3] = (avantdernier[index] - price[index]) / (1);
		
		for (std::size_t i = index-10; i < index+10; i++)
		{
			std::cout << stock[i] << " : " << price[i] << std::endl;
		}
		return solution;
		/*std::vector<double> coef = dauphine::Mid_diag_coeff(mesh, param, false);
		for (std::size_t i = 0; i < 50; i++)
		{
			std::cout << stock[i] << " : " << coef[i] << std::endl;
		}*/
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
	double maturity = 1;
	bool istrue = true;

	std::cout << "BS Price is:"<< dauphine::bs_price(spot, strike, volatility, maturity, istrue) << std::endl;


	std::cout << "Nicholson Crank:" << std::endl;	
	std::vector<double> solution = dauphine::essai(spot);
	std::cout << "Nicholson Price for S = "<< spot<< " is : " << solution[0] << std::endl;
	std::cout << "The Delta is " << solution[1] << std::endl;
	std::cout << "The Gamma is " << solution[2] << std::endl;
	std::cout << "The Theta is " << solution[3] <<std::endl;
    return 0;
}
