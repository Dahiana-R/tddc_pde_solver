#ifndef Solver_HPP
#define Solver_HPP
#include <iostream>
#include "Grille.hpp"
#include "Parameters.hpp"
#include "Boundaries.hpp"
#include "Payoffs.hpp"
#include "Rates.hpp"
#include "Volatility.hpp"
#include <vector>

namespace dauphine
{// on solve, (faire une classe solveur?utile?)
	//Fonction principal
	std::vector<double> CrankNicholson(Grille mesh, Parameters param, Boundaries bound, std::vector<double>& precedent);

	std::vector<double> LinearTriDiagSolver(std::vector<double> d, std::vector<std::vector<double>> coefficients);

	//calcul des boundaries, à voir plus tard comment on fait avec la classe boundaries... En ebauche. Ou peut être le faire dans le mesh?
	std::vector<double> upperboundary(std::vector<double>);
	std::vector<double> lowerboundary(std::vector<double>);

	//Calcul vecteur expiry et right vector correspond au calcul de b dans AX=b
	std::vector<double> vectorpayoff(Boundaries bound);
	std::vector<double> rightvector(Grille mesh, Parameters param, std::vector<double> f_n1, Boundaries bound, std::vector<std::vector<double>> coefficients,size_t time);

	//calcul des coef
	std::vector<double> Mid_diag_coeff(Grille mesh, Parameters param, bool isright);
	std::vector<double> Upper_diag_coeff(Grille mesh, Parameters param, bool isright);
	std::vector<double> Lower_diag_coeff(Grille mesh, Parameters param, bool isright);

    //application du solver
    std::vector<double> solving(Parameters param, Grille mesh, Boundaries bound);

	std::vector<double> tridiagonalisateur(Parameters param, Grille mesh, Neumann Neu);

}

#endif
