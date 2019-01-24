#include "Rates.hpp"

namespace dauphine
{
    Rates::Rates()
    {
    }
    double Rates::getRate(double dx, double dt, double rate)
    {
        return rate; // fonction à changer selon le modèle utilisé, retourne une constante dans notre cas
    }
    Rates::~Rates()
    {
    }
}
