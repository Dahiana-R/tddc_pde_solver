#include "Parameters.hpp"
#include <vector>

namespace dauphine
{
	Parameters::Parameters(double volatility, double rate, double theta)
		: param({ volatility,rate,theta })
	{
		/*param[0] = volatility;
		param[1] = rate;
		param[2] = theta;*/
	}
	double Parameters::GetVol() const{
		return param[0];
	}
	double Parameters::GetRate() const{
		return param[1];
	}
	double Parameters::GetTheta() const{
		return param[2];
	}
	Parameters::~Parameters() {

	}
}