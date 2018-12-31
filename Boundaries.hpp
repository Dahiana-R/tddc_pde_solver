#ifndef Boundaries_HPP
#define Boundaries_HPP
#include "Grille.hpp"
#include "Parameters.hpp"
#include <vector>

namespace dauphine
{// définir les boundaries faire une sous classe pour condition de Neuman/Dirichlet?
	class Boundaries {
	public:
		Boundaries(Grille mesh, Parameters param, double(*f)(double x));
		~Boundaries();
		std::vector<double> getupercondition();
		std::vector<double> getlowercondition();

	private:
		std::vector<double> UperCondition;
		std::vector<double> LowerCondition;
		std::vector<double> Payoff;
	};
}

#endif