#pragma once
#include "Particle.h"
#include "ParticleContainer.h"


namespace Simulation
{
	class StateWriter
	{
		static void writeStateToFile(char * filename, ParticleContainer& container);
	};
}