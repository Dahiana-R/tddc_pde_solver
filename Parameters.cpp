#include "Parameters.hpp"
#include <vector>

namespace dauphine
{
	Parameters::Parameters(double volatility, double rate, double theta)
		: m_volatility(volatility), m_rate(rate), m_theta(theta)//param({ volatility,rate,theta })
	{
//        param[0] = volatility;
//        param[1] = rate;
//        param[2] = theta;
	}
	double Parameters::GetVol() const{
		//return param[0];
		return m_volatility;
	}
	double Parameters::GetRate() const{
		//return param[1];
		return m_rate;
	}
	double Parameters::GetTheta() const{
		//return param[2];
		return m_theta;
	}
	Parameters::~Parameters() {

	}
}
