#pragma once
#include <vector>

#include "Particle.h"
#include "ParticleHandler.h"
#include "FileReader.h"

namespace Simulation
{
	/// <summary> Container class for managing particles
	class ParticleContainer
	{
	public:
		ParticleContainer(){}
		ParticleContainer(char* filename);
		
		/// <returns> Number of Particles; 
		int count()
		{
			return particles.size();
		}
		
		/// <returns> Particle at location i
		Particle& operator[](int i)
		{
			return particles[i];
		}


		void iterateParticles(ParticleHandler& handler);
		void iterateParticlePairs(ParticleHandler& handler);

	private:
		std::vector<Particle> particles;
	};
};
