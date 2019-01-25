#ifndef Boundaries_HPP
#define Boundaries_HPP
#include "Grille.hpp"
#include "Parameters.hpp"
#include "Payoffs.hpp"
#include "Rates.hpp"
#include "Volatility.hpp"
#include <vector>

namespace dauphine
{// définir les boundaries faire une sous classe pour condition de Neuman/Dirichlet
	class Boundaries {
	public:
		Boundaries(void);
		Boundaries(Grille mesh, Parameters param, double strike,double(*f)(double x,double strike));
		~Boundaries();
		std::vector<double> getupercondition();
		std::vector<double> getlowercondition();
		std::vector<double> getpayoff();
	protected:
		std::vector<double> Payoff;
	private:
		std::vector<double> UperCondition;
		std::vector<double> LowerCondition;
	};
	class Neumann: public Boundaries {
	public:
		Neumann(void);
		Neumann(Grille mesh, Parameters param, double(*f)(double x), std::vector<double> Neuman);
		~Neumann();
		std::vector<double> getneumann();
	private:
		std::vector<double> NeumannCoef;
	};
}

#endif