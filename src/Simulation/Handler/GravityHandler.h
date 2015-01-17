#pragma once
#include "ParticleHandler.h"

namespace Simulation
{
/// \class GravityHandler
/// \brief Computes gravitational force
class GravityHandler: public ParticleHandler
{
public:
	GravityHandler(double grav) :
			g(grav)
	{
	}

	void compute(Particle& p)
	{
		p.getF()[1] = p.getF()[1] + p.getM() * g;
	}

private:
	double g;
};
}
