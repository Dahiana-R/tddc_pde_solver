#ifndef Parameters_HPP
#define Parameters_HPP

#include <vector>

namespace dauphine
{
	class Parameters {
	public:
		Parameters(double volatility, double rate, double theta);
		double GetVol() const;
		double GetRate() const;
		double GetTheta() const;
		~Parameters();

	private:
		
		double m_volatility;
		double m_rate;
		double m_theta;
	};
}


#endif
