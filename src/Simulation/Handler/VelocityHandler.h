#pragma once
#include "ParticleHandler.h"

namespace Simulation
{
/// \class VelocityHandler
/// \brief Computes velocity of particle
class VelocityHandler: public ParticleHandlerTimeAware
{
public:
	VelocityHandler(double dt, int wallT) :
			ParticleHandlerTimeAware(dt), wallType(wallT)
	{
	}

	void compute(Particle& p)
	{
		if(p.getType() == wallType)
			return;
		utils::Vector<double, 3> term1 = p.getV();
		utils::Vector<double, 3> term2 = delta_t * (p.getOldF() + p.getF())
				* (1 / (2 * p.getM()));

		p.getV() = term1 + term2;
	}

private:
	int wallType;

};

}
