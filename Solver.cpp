#include "Solver.hpp"
#include <vector>
#include <math.h>

namespace dauphine
{
	double Mid_diag_coeff(Grille mesh, Parameters param, bool isright) {
		if (isright == false) {
			return (1. + param.GetTheta()*mesh.getdt()*((pow(param.GetVol(), 2) / pow(mesh.getdx(), 2)) + param.GetRate()));
		}
		else {
			return (1. + (param.GetTheta()-1.)*mesh.getdt()*((pow(param.GetVol(), 2) / pow(mesh.getdx(), 2)) + param.GetRate()));
		}
	}
	double Upper_diag_coeff(Grille mesh, Parameters param, bool isright) {
		if (isright == false) {
			return (param.GetTheta()*mesh.getdt()*((-0.5*pow(param.GetVol(), 2) / pow(mesh.getdx(), 2) + 0.25*(pow(param.GetVol(),2) - param.GetRate() / mesh.getdx()))));
		}
		else {
			return (param.GetTheta()-1.)*mesh.getdt()*((-0.5*pow(param.GetVol(), 2) / pow(mesh.getdx(), 2) + 0.25*(pow(param.GetVol(), 2) - param.GetRate() / mesh.getdx())));
		}
	}
	double Lower_diag_coeff(Grille mesh, Parameters param, bool isright) {
		if (isright == false) {
			return (param.GetTheta()*mesh.getdt()*(-(0.5*pow(param.GetVol(), 2) / pow(mesh.getdx(), 2) + 0.25*(pow(param.GetVol(), 2) - param.GetRate() / mesh.getdx()))));
		}
		else {
			return (param.GetTheta()-1.)*mesh.getdt()*(-(0.5*pow(param.GetVol(), 2) / pow(mesh.getdx(), 2) + 0.25*(pow(param.GetVol(), 2) - param.GetRate() / mesh.getdx())));
		}
	}

	std::vector<double> CrankNicholson(Grille mesh, Parameters param, Boundaries bound) {

		//paramètre de gauche(avec Theta)
		double aleft = Lower_diag_coeff(mesh, param,false);
		double bleft = Mid_diag_coeff(mesh, param,false);
		double cleft = Upper_diag_coeff(mesh, param,false);
		//paramètre de droite(donc Theta-1)
		double aright = Lower_diag_coeff(mesh, param,true);
		double bright = Mid_diag_coeff(mesh, param, true);
		double cright = Upper_diag_coeff(mesh, param, true);

		//vecteur contenant tous les coef, on les calcule une fois on est tranquille, penser à changer sur les autres fonctions si je ne l'ai pas fait.
		std::vector<double>coefficients{ aleft,bleft,cleft,aright,bright,cright };

		//on va stocker les prix au temps t-1 la dedans
		//on récupère expiry, mettre la fonction correctement....

		std::vector<double>pricebackward = vectorpayoff(bound);
		std::vector<double>d(pricebackward.size());

		for (size_t i = 0; i < mesh.getTimeNumber()-1 ; i++) {
			d = rightvector(mesh, param, pricebackward, bound,coefficients,i);
			pricebackward = LinearTriDiagSolver(d, coefficients);
		}

		return pricebackward;

	}

	//CF Wikipedia (tridiagonal matrix algorithm, j'ai utilisé la première méthode)
	//OK VALIDE
	std::vector<double> LinearTriDiagSolver(std::vector<double> d,std::vector<double> coefficients) {
		std::vector<double> test(d.size());
		double a = coefficients[0];
		double b = coefficients[1];
		double c = coefficients[2];
		std::vector<double> tempc(d.size());
		std::vector<double> tempd(d.size());
		for (size_t i = 0; i < d.size(); i++) {
			if (i == 0) {
				tempc[i] = c / b;
				tempd[i] = d[i] / b;
			}
			else {
				tempc[i] = c / (b - a * tempc[i - 1]);
				tempd[i] = (d[i] - a * tempd[i - 1]) / (b - a * tempc[i - 1]);
			}

		}
		for (int i = d.size() - 1; i >= 0; i--) {
			if (i == d.size() - 1) {
				test[i] = tempd[i];
			}
			else {
				test[i] = tempd[i] - tempc[i] * test[i + 1];
			}
		}
		return test;
	}

	//la fonction tourne, le fait que ca renvoie ou non le bon résultat est sujet à débat	.
	std::vector<double> rightvector(Grille mesh, Parameters param, std::vector<double> f_n1, Boundaries bound, std::vector<double> coefficients,size_t time) {

		std::vector<double> test(f_n1.size());
		double a = coefficients[3];
		double aleft = coefficients[0];
		double b = coefficients[4];
		double c = coefficients[5];
		double cleft = coefficients[2];
		for (size_t i = 0; i < f_n1.size(); i++) {
			if (i == 0) { //le - devant le coef correspond au temps t(quand on passe le vecteur à droite), le reste au temps t+1
				test[i] = -aleft * bound.getlowercondition()[time+1] + a* bound.getlowercondition()[time] + b * f_n1[i] + c * f_n1[i + 1]  ;
			}
			else if (i == f_n1.size()-1) {
				test[i] = a * f_n1[i - 1] + b * f_n1[i] + c * bound.getupercondition()[time] - cleft * bound.getupercondition()[time+1];
			}
			else {
				test[i] = a * f_n1[i - 1] + b * f_n1[i] + c * f_n1[i + 1];
			}
			
		}
		return test;

	}

	//OK VALIDE
	//calcul du vecteur expiry, on prend celui de boundaries, on enlève juste les conditions initiales.
	std::vector<double> vectorpayoff(Boundaries bound) {
		std::vector<double> stockprice = bound.getpayoff();
		stockprice.pop_back();
		stockprice.erase(stockprice.begin());
		return stockprice;
	}
}