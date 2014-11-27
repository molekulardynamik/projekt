#pragma once
#include <vector>
#include <list>

#include "utils/Vector.h"
#include "Particle.h"

namespace Simulation
{
	class ParticleGenerator
	{
	public:
		static void generateCuboid(
			utils::Vector<double, 3> bottomLeftFront, 
			utils::Vector<int, 3 > numParticles, 
			double h, 
			double mass, 
			utils::Vector<double, 3 > initialVelocity, 
			double meanValue,
			std::list<Particle>& particles);
	};
}
