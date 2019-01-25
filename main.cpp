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

int main(int argc, char* argv[])
{
    double spot;
    double strike;
    double volatility;
    double maturity;
    double rate;
    double theta;
    double time_step_value;
    double space_step;
    char product;
    char time_step;
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
    
    std::vector<char> time_step_list = {'A', 'B', 'C', 'D'}; //vect of possible time steps
    
    std::cout << "Please choose your time step." << std::endl;
    std::cout << "a) Daily working days: 1./252. \nb) Daily: 1./365, \nc) Monthly: 30./365, \nd) Custom input in yearly decimals" << std::endl;
    
    std::cin >> time_step;
    time_step = toupper(time_step);
    
    while(std::find(time_step_list.begin(), time_step_list.end(), time_step) == time_step_list.end())
    {
        std::cout << "Wrong input, please enter one of the proposed options. " << std::endl;
        std::cin >> time_step;
        time_step = toupper(time_step);
    };
  
    if (time_step == 'A'){
        time_step_value = 1./252.;
        
    }
    else if (time_step == 'B'){
        time_step_value = 1./365.;
        
    }
    else if (time_step == 'C'){
        time_step_value = 30./365.;
        
    }
    else if (time_step == 'D'){
        std::cout << "yearly decimals: eg. 0.5 for semi-annually, 1 for yearly" << std::endl;
        while (!(std::cin >> time_step_value)) {
            std::cin.clear();
            std::cin.ignore(512, '\n');
            std::cout<< "You have entered a wrong input "<<std::endl;
        };
        
    };
    
    std::cout << "Total Space steps (Optimal: 1000):" << std::endl;
    
    while (!(std::cin >> space_step)) {
        std::cin.clear();
        std::cin.ignore(512, '\n');
        std::cout<< "You have entered a wrong input. Total Space Steps: "<<std::endl;
        
    }
    
    dauphine::Parameters param(volatility, rate, theta);
    
    dauphine::Grille mesh(maturity, spot, volatility, time_step_value, space_step);
    
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
