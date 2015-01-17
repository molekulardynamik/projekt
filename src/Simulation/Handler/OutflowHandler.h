#pragma once
#include "ParticleHandler.h"

namespace Simulation
{
/// \class OutflowHandler
/// \brief Handles outflow in boundaries
class OutflowHandler: public ParticleHandler
{
public:
	OutflowHandler() :
			ParticleHandler()
	{
	}

	void compute(Particle& p)
	{
	}
};
}
