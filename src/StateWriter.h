#pragma once
#include "Particle.h"
#include "ParticleContainer.h"


namespace Simulation
{
	class StateWriter
	{
	public:
		static void writeStateToFile(const char * filename, ParticleContainer& container);
	};
}