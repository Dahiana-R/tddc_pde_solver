#ifndef Payoffs_hpp
#define Payoffs_hpp

#include <iostream>

namespace dauphine
{
    class Payoffs {
    public:
        Payoffs();
        static double call(double spot, double strike);// fonction statique pour éviter de créer un objet payoff, utile pour mettre en paramètre dans l'objet boundaries
        static double put(double spot, double strike);// fonction statique pour éviter de créer un objet payoff, utile pour mettre en paramètre dans l'objet boundaries
        ~Payoffs();
        
    private:
//        double Strike;
//        double Spot;
    };
}

#endif /* Payoffs_hpp */

