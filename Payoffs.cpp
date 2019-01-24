#include "Payoffs.hpp"

namespace dauphine
{
    Payoffs::Payoffs()
    {
    }
    double Payoffs::getThePayoff(double spot, double strike)
    {
        return std::max(spot - strike, 0.);
    }
    Payoffs::~Payoffs()
    {
    }
}
