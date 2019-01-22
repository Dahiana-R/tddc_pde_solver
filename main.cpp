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
		Grille mesh(1., 100., 0.2, (1. / 252.), 1000, 0.2);
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

}

int main(int argc, char* argv[])
{
	double spot;
	double strike;
	double volatility;
	double maturity;
	bool istrue = true;

    //Saisie des données initiales
    std::cout << "Underlying Spot Price:" << std::endl;
    std::cin >> spot;
    std:: cout << "Strike Price:" << std::endl;
    std::cin >> strike;
    std::cout << "Volatility:" << std::endl;
    std::cin >> volatility;
    std::cout << "Maturity (in days):" << std::endl;
    std::cin >> maturity;
    std::cout << " " << std::endl;
    
	std::cout << "BS Price is:"<< dauphine::bs_price(spot, strike, volatility, maturity, istrue) << std::endl;


	std::cout << "Nicholson Crank:" << std::endl;	
	std::vector<double> solution = dauphine::essai(spot);
	std::cout << "Nicholson Price for S = "<< spot<< " is : " << solution[0] << std::endl;
	std::cout << "The Delta is " << solution[1] << std::endl;
	std::cout << "The Gamma is " << solution[2] << std::endl;
	std::cout << "The Theta is " << solution[3] <<std::endl;
    return 0;
}
