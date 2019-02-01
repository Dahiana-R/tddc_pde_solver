#ifndef Volatility_hpp
#define Volatility_hpp

#include <iostream>

namespace dauphine
{
    class Volatility {
    public:
        Volatility();
        // Why a static method in a class? A free functino would be enough
        static double getVolatility(double dx, double dt, double volatility);
        ~Volatility();
        
    private:

    };
}

#endif /* Volatility_hpp */
