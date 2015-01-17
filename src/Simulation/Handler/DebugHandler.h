#pragma once
#include "ParticleHandler.h"

#include <iostream>

namespace Simulation
{

class DebugHandler: public ParticleHandler
{
public:
	DebugHandler() :
		ParticleHandler()
	{
	}

	/// Nonsymmetric computation
	void compute(Particle& p1, Particle& p2)
	{
		std::cout << "combine " << p1.getX()[0] << ", " << p1.getX()[1] << " and " << p2.getX()[0] << ", " << p2.getX()[1] << std::endl;
	}
};
}
