#pragma once
#include "ParticleHandler.h"

namespace Simulation
{
/// \class GravityHandler
/// \brief Computes gravitational force
class GravityHandler: public ParticleHandler
{
public:
	GravityHandler(utils::Vector<double, 3> grav) :
			g(grav)
	{
	}

	void compute(Particle& p)
	{
		p.getF() = p.getF() + g * p.getM();
	}

private:
	utils::Vector<double, 3> g;
};
}
