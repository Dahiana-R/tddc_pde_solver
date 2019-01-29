#include "Boundaries.hpp"
#include <vector>
#include <cmath>

namespace dauphine
{
	Boundaries::Boundaries(Grille mesh,Parameters param, double strike, double(*f)(double x, double strike))
	{
        // Too complicated, Dirichlet boundary means keeping the previous value.
        // So if you have the following tridiag problem:

        // Assuming the following system (with K = N - 1):
        // (b0 c0   ...  0) (x0)   (d0)
        // (a1 b1 c1 ... 0) (x1)   (d1)
        //       ...        (..) = (..)
        // (  ... aK bK cK) (xK)   (dK)
        // (   ...   aN bN) (xN)   (dN)
        // and the previous solution (f0 f1 ... fK fN)

        // Dirichlet sets the first and last lines of the matrix, and the first and last
        // values of d:
        // b0 = 1, c0 = 0, d0 = f0
        // aN = 0, bN = 1, dN = fN

        // Neuman does the following
        // b0 = -1, c0 = 1, d0 = f1 - f0
        // aN = -1, bN = 1, dN = fN - fK

		double dt = mesh.getdt();
		double rate = param.GetRate();
		double dX = mesh.GetTailleStock() - 1;
		Payoff = mesh.getStockVector();
		double spotSize = mesh.getdx().size();
		std::vector<double> upper_vect(mesh.getTimeNumber());
		std::vector<double> lower_vect(mesh.getTimeNumber());
		for (size_t i = 0; i < mesh.GetTailleStock(); i++) {
			Payoff[i] = f(Payoff[i], strike);
		}
		
		for (int i = 0; i< mesh.getTimeNumber(); i++) {
			upper_vect[i] = Payoff[dX] * exp(-i * dt*dauphine::Rates::getRate(mesh.getdx()[spotSize - 1], dt, rate));
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
