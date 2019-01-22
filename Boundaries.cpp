#include "Boundaries.hpp"
#include <vector>
#include <cmath>

namespace dauphine
{
	Boundaries::Boundaries(Grille mesh,Parameters param, double(*f)(double x))
	{//surement à modifier par la suite pour rentre le truc souple, "placebo" pour l'instant

		Payoff = mesh.getStockVector();
		std::vector<double> test_1(mesh.getTimeNumber());
		std::vector<double> test_2(mesh.getTimeNumber());
		for (size_t i = 0; i < mesh.GetTailleStock(); i++) {
			Payoff[i] = f(Payoff[i]);
		}
		
		for (int i = 0; i< mesh.getTimeNumber(); i++) {
			test_1[i] = Payoff[mesh.GetTailleStock()-1] * exp(- i* mesh.getdt()*param.GetRate());
			test_2[i] = Payoff[0] * exp(- i * mesh.getdt()*param.GetRate());
		}
		UperCondition = test_1;
		LowerCondition = test_2;
	}

	Boundaries::~Boundaries() {

	}
	std::vector <double>Boundaries::getupercondition(){
		return UperCondition;
	}
	std::vector <double>Boundaries::getlowercondition(){
		return LowerCondition;
	}
	std::vector <double>Boundaries::getpayoff() {
		return Payoff;
	}
}
