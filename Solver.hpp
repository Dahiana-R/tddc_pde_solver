#ifndef Solver_HPP
#define Solver_HPP
#include "Grille.hpp"
#include "Parameters.hpp"
#include "Boundaries.hpp"
#include <vector>

namespace dauphine
{// on solve, (faire une classe solveur?utile?)
	//Fonction principal
	std::vector<double> CrankNicholson(Grille mesh, Parameters param, Boundaries bound, double(*payoff)(double x));
	std::vector<double> LinearTriDiagSolver(Grille mesh, Parameters param, std::vector<double> d, std::vector<double> coefficients);

	//calcul des boundaries, à voir plus tard comment on fait avec la classe boundaries... En ébauche. Ou peut être le faire dans le mesh?
	std::vector<double> upperboundary(std::vector<double>);
	std::vector<double> lowerboundary(std::vector<double>);

	//Calcul vecteur expiry et right vector correspond au calcul de b dans AX=b
	std::vector<double> vectorpayoff(double(*payoff)(double x), Grille mesh);
	std::vector<double> rightvector(Grille mesh, Parameters param, std::vector<double> f_n1, Boundaries bound, std::vector<double> coefficients,double time);

	//calcul des coef
	double Mid_diag_coeff(Grille mesh, Parameters param, bool isright);
	double Upper_diag_coeff(Grille mesh, Parameters param, bool isright);
	double Lower_diag_coeff(Grille mesh, Parameters param, bool isright);

}

#endif