#include "Boundaries.hpp"
#include <vector>

namespace dauphine
{
	Boundaries::Boundaries(Grille mesh,Parameters param, double(*f)(double x))
	{//surement à modifier par la suite pour rentre le truc souple, "placebo" pour l'instant

		Payoff = mesh.getStockVector();
		for (size_t i = 0; i <= mesh.GetTailleStock(); i++) {
			Payoff[i] = f(Payoff[i]);
		}
		
		for (size_t i = mesh.getTimeNumber(); i >= 0; i--) {
			UperCondition[i] = Payoff[mesh.GetTailleStock()] * exp(-mesh.getdt()*param.GetRate());
			LowerCondition[i] = Payoff[0] * exp(-mesh.getdt()*param.GetRate());
		}
	}

	Boundaries::~Boundaries() {

	}
	std::vector <double>Boundaries::getupercondition(){
		return UperCondition;
	}
	std::vector <double>Boundaries::getlowercondition(){
		return LowerCondition;
	}
}