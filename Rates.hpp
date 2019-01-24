#ifndef Rates_hpp
#define Rates_hpp

#include <iostream>

namespace dauphine
{
    class Rates {
    public:
        Rates();
        static double getRate(double dx, double dt, double rate);
        ~Rates();
        
    private:
        
    };
}

#endif /* Rates_hpp */

