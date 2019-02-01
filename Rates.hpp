#ifndef Rates_hpp
#define Rates_hpp

#include <iostream>

namespace dauphine
{
    class Rates {
    public:
        Rates();
        // Why a static method in a class? A free functino would be enough
        static double getRate(double dx, double dt, double rate);
        ~Rates();
        
    private:
        
    };
}

#endif /* Rates_hpp */

