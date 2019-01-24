#ifndef Payoffs_hpp
#define Payoffs_hpp

#include <iostream>

namespace dauphine
{
    class Payoffs {
    public:
        Payoffs();
        static double getThePayoff(double spot, double strike);
        ~Payoffs();
        
    private:
//        double Strike;
//        double Spot;
    };
}

#endif /* Payoffs_hpp */

