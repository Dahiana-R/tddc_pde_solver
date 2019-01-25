#include "Parameters.hpp"
#include <vector>

namespace dauphine
{
	Parameters::Parameters(double volatility, double rate, double theta)
		: m_volatility(volatility), m_rate(rate), m_theta(theta)
	{

	}
	double Parameters::GetVol() const{

		return m_volatility;
	}
	double Parameters::GetRate() const{

		return m_rate;
	}
	double Parameters::GetTheta() const{

		return m_theta;
	}
	Parameters::~Parameters() {

	}
}
