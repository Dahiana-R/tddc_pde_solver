#include <iostream>
#include <algorithm>
#include <cmath>
#include <limits>
#include "closed_form.hpp"
#include "Solver.hpp"
#include "Parameters.hpp"
#include "Grille.hpp"
#include "Boundaries.hpp"
#include "Payoffs.hpp"



//    double payoff(double x) {
//        return std::max(x-100, 0.);
//    }



    std::vector<double> essai()
    {
        double spot;
        double strike;
        double volatility;
        double maturity;
        double rate;
        double theta;
        int product;
        
        std::cout << "1.Call Option \n2.Put Option, \n3.Other Products:" << std::endl;
        std::cin >> product;
        if (product == 3){
            std::cout << "Not available yet, please request implementation" << std::endl;
            exit(0);

        }

        std::cout << "Underlying Spot Price:" << std::endl;
        std::cin >> spot;
        std:: cout << "Strike Price:" << std::endl;
        std::cin >> strike;
        std::cout << "Volatility:" << std::endl;
        std::cin >> volatility;
        std::cout << "Risk free rate:" << std::endl;
        std::cin >> rate;
        std::cout << "Maturity (in years):" << std::endl;
        std::cin >> maturity;
        std::cout << "Theta:" << std::endl;
        std::cin >> theta;
                bool istrue = true;
		/*
		//COEF POUR NEUMAN
	double ATheta(Grille mesh, Parameters param, bool isright) {
			if (isright == false) {
				return (1. + param.GetTheta()*mesh.getdt()*(-0.5*pow(param.GetVol(), 2) / pow(mesh.getdx()[0], 2) + param.GetRate() - 0.5 * (pow(param.GetVol(), 2) - param.GetRate()))) ;
			}
			else {
				return (1. + (param.GetTheta() - 1.)*mesh.getdt()*(-0.5*pow(param.GetVol(), 2) / pow(mesh.getdx()[0], 2) + param.GetRate() - 0.5 * (pow(param.GetVol(), 2) - param.GetRate())));
			}
		
	}
	double BTheta(Grille mesh, Parameters param, bool isright) {
		if (isright == false) {
			return (param.GetTheta()*mesh.getdt()*(pow(param.GetVol(), 2) / pow(mesh.getdx()[0], 2) + 0.5 *(pow(param.GetVol(), 2) - param.GetRate())/ mesh.getdx()[0]));
		}
		else {
			return ((param.GetTheta() - 1.)*mesh.getdt()*(pow(param.GetVol(), 2) / pow(mesh.getdx()[0], 2) + 0.5 *(pow(param.GetVol(), 2) - param.GetRate()) / mesh.getdx()[0]));
		}
	}
	

	double CTheta(Grille mesh, Parameters param, bool isright) {
		if (isright == false) {
			return (param.GetTheta()*mesh.getdt()*(-0.5*pow(param.GetVol(), 2) / pow(mesh.getdx()[0], 2)));
		}
		else {
			return ((param.GetTheta() - 1.)*mesh.getdt()*(-0.5*pow(param.GetVol(), 2) / pow(mesh.getdx()[0], 2)));
		}
	}
	//FIN COEF NEUMAN;	
		*/
        
        dauphine::Parameters param(volatility, rate, theta);
		
		//test pour un dx fixé en prenant comme frontiere spot +- 5stddev racine T. On centre sur le spot.
        dauphine::Grille mesh(maturity, spot, volatility, (1. / 252.), 1000, 0.2);
        

        std::vector<double> solution;
        
        if (product == 1){
            dauphine::Boundaries bound(mesh, param, strike, dauphine::Payoffs::call);
            solution = dauphine::solving(param,  mesh,  bound);
            solution.push_back(dauphine::bs_price(spot, strike, volatility, maturity, istrue));

        }
        
        else if(product == 2){
            dauphine::Boundaries bound(mesh, param, strike, dauphine::Payoffs::put);
            solution = dauphine::solving(param,  mesh,  bound);
            solution.push_back(dauphine::bs_price(spot, strike, volatility, maturity, false));
            //solution.push_back(0.000);
        }
        


        //dauphine::Boundaries bound(mesh, param, strike, dauphine::Payoffs::getThePayoff); // en dernier paramètre on prend la fonction statique du payoff  


        solution.push_back(spot); // a modif
		return solution;
        

	}



int main(int argc, char* argv[])
{
    double spot;
    double strike;
    double volatility;
    double maturity;
    double rate;
    double theta;
    char product;
    std::vector<double> solution;

    
    std::vector<char> product_list = {'A', 'B', 'C'}; //vect of possible product to adjust if new products added
    
    // inputs for pricing, limited inputs, rerequest values if they are out of scope
    std::cout << "Please choose your product." << std::endl;
    std::cout << "a) Call Option \nb) Put Option, \nc) Other Products" << std::endl;
    
    std::cin >> product;
    product = toupper(product);
    
    while(std::find(product_list.begin(), product_list.end(), product) == product_list.end())
    {
        std::cout << "Wrong input, please enter one of the proposed options. " << std::endl;
        std::cin >> product;
        product = toupper(product);
    };

    if (product == 'C'){
        std::cout << "Not available yet, please request implementation" << std::endl;
        exit(0);
        
    };

    std::cout << "Underlying Spot Price:" << std::endl;

    while (!(std::cin >> spot)) {
        std::cin.clear();
        std::cin.ignore(512, '\n');
        std::cout<< "You have entered a wrong input. Underlying Spot Price: "<<std::endl;

    }

    std:: cout << "Strike Price:" << std::endl;
    while (!(std::cin >> strike)) {
        std::cin.clear();
        std::cin.ignore(512, '\n');
        std::cout<< "You have entered a wrong input. Strike: "<<std::endl;
        
    }
    
    std::cout << "Volatility in decimals" << std::endl;
    while (!(std::cin >> volatility)) {
        std::cin.clear();
        std::cin.ignore(512, '\n');
        std::cout<< "You have entered a wrong input. Volatility: "<<std::endl;
        
    }

    std::cout << "Risk free rate:" << std::endl;
    while (!(std::cin >> rate)) {
        std::cin.clear();
        std::cin.ignore(512, '\n');
        std::cout<< "You have entered a wrong input. Rate: "<<std::endl;
        
    }

    std::cout << "Maturity (in years):" << std::endl;
    while (!(std::cin >> maturity)) {
        std::cin.clear();
        std::cin.ignore(512, '\n');
        std::cout<< "You have entered a wrong input. Maturity: "<<std::endl;
        
    }

    std::cout << "Theta, between 0 and 1:" << std::endl;
    
    while (!(std::cin >> theta) or theta< 0 or theta > 1) {
            std::cin.clear();
            std::cin.ignore(512, '\n');
            std::cout<< "You have entered a wrong input. Theta: "<<std::endl;
            
        }
    
    dauphine::Parameters param(volatility, rate, theta);
    
    dauphine::Grille mesh(maturity, spot, volatility, (1. / 252.), 1000, 0.2);
    
    if (product == 'A'){
        dauphine::Boundaries bound(mesh, param, strike, dauphine::Payoffs::call);
        solution = dauphine::solving(param,  mesh,  bound);
        solution.push_back(dauphine::bs_price(spot, strike, volatility, maturity, true));
    }
    
    else if(product == 'B'){
        dauphine::Boundaries bound(mesh, param, strike, dauphine::Payoffs::put);
        solution = dauphine::solving(param,  mesh,  bound);
        solution.push_back(dauphine::bs_price(spot, strike, volatility, maturity, false));
    }

    if(solution[4]!= 0.000){
        std::cout << "BS Price is:"<< solution[4] << std::endl;
    }
    else {
        // in case of additional products is BS price is not available, add solution.push_back(0.000) instead of: solution.push_back(dauphine::bs_price(s));
        std::cout << "BS Price is not available for this product" << std::endl;
    }

	std::cout << "Nicholson Price for S = "<< spot << " is : " << solution[0] << std::endl;
	std::cout << "The Delta is " << solution[1] << std::endl;
	std::cout << "The Gamma is " << solution[2] << std::endl;
	std::cout << "The Theta is " << solution[3] <<std::endl;
    return 0;
}
