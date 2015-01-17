#pragma once
#include "ParticleHandler.h"

namespace Simulation
{
/// \class PositionHandler
/// \brief Computes position of particle
class PositionHandler: public ParticleHandlerTimeAware
{
public:
	PositionHandler(double dt) :
			ParticleHandlerTimeAware(dt)
	{
	}

	void compute(Particle& p)
	{
		utils::Vector<double, 3> term1 = p.getX();
		utils::Vector<double, 3> term2 = delta_t * p.getV();
		utils::Vector<double, 3> term3 = pow(delta_t, 2) * p.getF()
				* (1 / (2 * p.getM()));

		p.getX() = term1 + term2 + term3;
	}
};
}
