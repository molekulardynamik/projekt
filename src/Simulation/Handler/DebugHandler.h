#pragma once
#include "ParticleHandler.h"

#include <iostream>

namespace Simulation
{

/// \class DebugHandler
/// \brief Handler for debuging simulation, should only be used with small particle counts
class DebugHandler: public ParticleHandler
{
public:
	DebugHandler() :
		ParticleHandler()
	{
	}

	/// prints x and y coordinate of the combined particles
	void compute(Particle& p1, Particle& p2)
	{
		std::cout << "combine " << p1.getX()[0] << ", " << p1.getX()[1] << " and " << p2.getX()[0] << ", " << p2.getX()[1] << std::endl;
	}
};
}
