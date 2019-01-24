#include "Payoffs.hpp"
#include <algorithm>
namespace dauphine
{
    Payoffs::Payoffs()
    {
    }
    double Payoffs::getThePayoff(double spot, double strike)
    {
        return std::max(spot - strike, 0.); // fonction à adapter selon le payoff, un call dans notre cas
    };
    
    double Payoffs::call(double spot, double strike)
    {
        return std::max(spot - strike, 0.);
    };
    double Payoffs::put(double spot, double strike)
    {
        return std::max(strike - spot, 0.);
    };
    Payoffs::~Payoffs()
    {
    }
}
