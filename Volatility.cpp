#include "Volatility.hpp"

namespace dauphine
{
    Volatility::Volatility()
    {
    }
    double Volatility::getVolatility(double dx, double dt, double volatility)
    {
        return volatility; // fonction à changer selon le modèle utilisé, retourne une constante dans notre cas
    }
    Volatility::~Volatility()
    {
    }
}
