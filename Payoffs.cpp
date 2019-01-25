#include "Payoffs.hpp"
#include <algorithm>
namespace dauphine
{
    Payoffs::Payoffs()
    {
    }
    
    // For other products add the corresponding function at maturity, if there are more arguments than the spot and strike adjust the function in Boundaries too

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
