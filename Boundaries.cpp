#include "Boundaries.hpp"
#include <vector>
#include <cmath>

namespace dauphine
{
	Boundaries::Boundaries(Grille mesh,Parameters param, double strike, double(*f)(double x, double strike))
	{//surement à modifier par la suite pour rentre le truc souple, "placebo" pour l'instant
		double dt = mesh.getdt();
		double rate = param.GetRate();
		double dX = mesh.GetTailleStock() - 1;
		Payoff = mesh.getStockVector();
		std::vector<double> test_1(mesh.getTimeNumber());
		std::vector<double> test_2(mesh.getTimeNumber());
		for (size_t i = 0; i < mesh.GetTailleStock(); i++) {
			Payoff[i] = f(Payoff[i], strike);
		}
		
		for (int i = 0; i< mesh.getTimeNumber(); i++) {
			test_1[i] = Payoff[dX] * exp(-i * dt* rate);// dauphine::Rates::getRate(mesh.getdx()[dX], dt, rate));
			test_2[i] = Payoff[0] * exp(- i * dt*dauphine::Rates::getRate(mesh.getdx()[0], dt, rate));
		}
		UperCondition = test_1;
		LowerCondition = test_2;
	}
	Boundaries::Boundaries(void) {

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
	
	Neumann::Neumann(Grille mesh, Parameters param, double(*f)(double x), std::vector<double> Neuman) 
	{
		Payoff = mesh.getStockVector();
		std::vector<double> test(mesh.GetTailleStock());
		for (size_t i = 0; i < mesh.GetTailleStock(); i++) {
			Payoff[i] = f(Payoff[i]);
			test[i] = Neuman[i];
		}
		NeumannCoef = test;
	}

	Neumann::~Neumann() {

	}
	std::vector<double> Neumann::getneumann(){
		return NeumannCoef;
	}
}
