#ifndef Boundaries_HPP
#define Boundaries_HPP
#include "Grille.hpp"
#include "Parameters.hpp"
#include "Payoffs.hpp"
#include "Rates.hpp"
#include "Volatility.hpp"
#include <vector>

namespace dauphine
{// definir les boundaries faire une sous classe pour condition de Neuman/Dirichlet
    // Boundaries should be a interface (with pure virtual methods), inherited by
    // Dirichlet and Neumann conditions, would be more meaninful.
    // Missing entity semantic
    // - virtual destructor (here you have a potential leak with Boundaries* b = new Neumann(...)
    // - deleted copy and move constructors / assign operators to prevent incomplete copies
	class Boundaries {
	public:
		Boundaries(void);
		Boundaries(Grille mesh, Parameters param, double strike,double(*f)(double x,double strike));
		~Boundaries();
		std::vector<double> getuppercondition();
		std::vector<double> getlowercondition();
		std::vector<double> getpayoff();
	protected:
		std::vector<double> Payoff;
	private:
		std::vector<double> UpperCondition;
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
