#include "Boundaries.hpp"
#include <vector>
#include <cmath>

namespace dauphine
{
	Boundaries::Boundaries(Grille mesh,Parameters param, double strike, double(*f)(double x, double strike))
	{
		double dt = mesh.getdt();
		double rate = param.GetRate();
		double dX = mesh.GetTailleStock() - 1;
		Payoff = mesh.getStockVector();
		std::vector<double> upper_vect(mesh.getTimeNumber());
		std::vector<double> lower_vect(mesh.getTimeNumber());
		for (size_t i = 0; i < mesh.GetTailleStock(); i++) {
			Payoff[i] = f(Payoff[i], strike);
		}
		
		for (int i = 0; i< mesh.getTimeNumber(); i++) {
			upper_vect[i] = Payoff[dX] * exp(-i * dt* rate);
			lower_vect[i] = Payoff[0] * exp(- i * dt*dauphine::Rates::getRate(mesh.getdx()[0], dt, rate));
		}
		UpperCondition = upper_vect;
		LowerCondition = lower_vect;
	}
	Boundaries::Boundaries(void) {

	}
	Boundaries::~Boundaries() {

	}
	std::vector <double>Boundaries::getuppercondition(){
		return UpperCondition;
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
		std::vector<double> test_neuman(mesh.GetTailleStock());
		for (size_t i = 0; i < mesh.GetTailleStock(); i++) {
			Payoff[i] = f(Payoff[i]);
			test_neuman[i] = Neuman[i];
		}
		NeumannCoef = test_neuman;
	}

	Neumann::~Neumann() {

	}
	std::vector<double> Neumann::getneumann(){
		return NeumannCoef;
	}
}
